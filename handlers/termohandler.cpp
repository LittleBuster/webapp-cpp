#include "termohandler.h"
#include "ext.h"
#include <iostream>


TermoHandler::TermoHandler(const shared_ptr<ITermoClient> &termo,
                           const shared_ptr<ILog> log):
                           _termo(move(termo)), _log(move(log))
{
}

void TermoHandler::simpleAnsware(bool result, const shared_ptr<ITcpClient> &client)
{
    string answ = "HTTP/1.1 200 OK\r\n"
                  "Content-Type: application/json; charset=UTF-8\r\n\r\n"
                  "{\"module\": \"termo\", \"result\": \"";
    if (result)
        answ += "ok\"}";
    else
        answ += "fail\"}";

    client->send(answ.c_str(), answ.length());
}

void TermoHandler::tempAnsware(float temp, const shared_ptr<ITcpClient> &client)
{
    string answ = "HTTP/1.1 200 OK\r\n"
                  "Content-Type: application/json; charset=UTF-8\r\n\r\n"
                  "{\"module\": \"termo\", \"result\": \"ok\", \"temp\": "
                  + ext::ftoa(temp) + "}";

    client->send(answ.c_str(), answ.length());
}

void TermoHandler::handler(const string &req, const shared_ptr<ITcpClient> &client, mutex &mtx)
{
    vector<string> args;

    if (req == "get_temp") {
        float mt;

        try {
            mt = _termo->getMaxTemp();
        }
        catch (const string &err) {
            mtx.lock();
            _log->local("Termo(C): fail getting max temperature.", LOG_ERROR);
            mtx.unlock();
            return;
        }
        try {
            tempAnsware(mt, client);
        }
        catch (const string &err) {
            mtx.lock();
            _log->local("Fail sending temp answare: " + err, LOG_ERROR);
            mtx.unlock();
        }
        return;
    }

    try {
        ext::split_string(req, '=', args);
    }
    catch(...) {
        mtx.lock();
        _log->local("Fail parsing termo request.", LOG_ERROR);
        mtx.unlock();

        try {
            simpleAnsware(false, client);
        }
        catch (const string &err) {
            mtx.lock();
            _log->local("Fail sending temp answare: " + err, LOG_ERROR);
            mtx.unlock();
        }
        return;
    }

    if (args[0] == "temp_set") {
        float newTemp;

        try {
            newTemp = atof(args[1].c_str());
        }
        catch (...) {
            mtx.lock();
            _log->local("Fail parsing max temperature.", LOG_ERROR);
            mtx.unlock();

            try {
                simpleAnsware(false, client);
            }
            catch (const string &err) {
                mtx.lock();
                _log->local("Fail sending temp answare: " + err, LOG_ERROR);
                mtx.unlock();
            }
            return;
        }

        try {
            _termo->setMaxTemp(newTemp);
        }
        catch (...) {
            try {
                simpleAnsware(false, client);
            }
            catch (const string &err) {
                mtx.lock();
                _log->local("Fail sending temp answare: " + err, LOG_ERROR);
                mtx.unlock();
            }
            return;
        }
        try {
            simpleAnsware(true, client);
        }
        catch (const string &err) {
            mtx.lock();
            _log->local("Fail sending temp answare: " + err, LOG_ERROR);
            mtx.unlock();
        }
        return;
    }

    mtx.lock();
    _log->local("Unknown termo request.", LOG_WARNING);
    mtx.unlock();

    try {
        simpleAnsware(false, client);
    }
    catch (const string &err) {
        mtx.lock();
        _log->local("Fail sending temp answare: " + err, LOG_ERROR);
        mtx.unlock();
    }
}
