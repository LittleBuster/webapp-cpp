#include "termohandler.h"
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>


TermoHandler::TermoHandler(const shared_ptr<ITermoClient> &termo,
                           const shared_ptr<ILog> log):
                           _termo(move(termo)), _log(move(log))
{
}

bool TermoHandler::simpleAnsware(bool result)
{
    string answ = "HTTP/1.1 200 OK\r\n"
                  "Content-Type: application/json; charset=UTF-8\r\n\r\n"
                  "{\"module\": \"termo\", \"result\": \"";
    if (result)
        answ += "ok\"}";
    else
        answ += "fail\"}";

    try {
       // _client->send(answ.c_str(), answ.length());
    } catch(const string &err) {
       // _mtx.lock();
        _log->local("Termo(H): " + err, LOG_ERROR);
      //  _mtx.unlock();
        return false;
    }
    return true;
}

bool TermoHandler::tempAnsware(float temp)
{
    string answ = "HTTP/1.1 200 OK\r\n"
                  "Content-Type: application/json; charset=UTF-8\r\n\r\n"
                  "{\"module\": \"termo\", \"result\": \"ok\", \"temp\": "
                  + boost::lexical_cast<string>(temp) + "}";

    try {
      //  _client->send(answ.c_str(), answ.length());
    } catch(const string &err) {
       // _mtx.lock();
        _log->local("Termo(H): " + err, LOG_ERROR);
       // _mtx.unlock();
        return false;
    }
    return true;
}

void TermoHandler::handler(const string &req)
{
    vector<string> args;

    if (req == "get_temp") {
        float mt;

        try {
            mt = _termo->getMaxTemp();
        }
        catch (const string &err) {
          //  _mtx.lock();
            _log->local("Termo(C): fail getting max temperature.", LOG_ERROR);
           // _mtx.unlock();
            return;
        }
        if (!tempAnsware(mt)) {
          //  _mtx.lock();
            _log->local("Fail sending temp answare.", LOG_ERROR);
          //  _mtx.unlock();
        }
        return;
    }

    try {
        boost::split(args, req, boost::is_any_of("="));
    }
    catch(...) {
       // _mtx.lock();
        _log->local("Fail parsing termo request.", LOG_ERROR);
       // _mtx.unlock();

        if (!simpleAnsware(false)) {
            //_mtx.lock();
            _log->local("Fail sending temp answare.", LOG_ERROR);
            //_mtx.unlock();
        }
        return;
    }

    if (args[0] == "temp_set") {
        float newTemp;

        try {
            newTemp = boost::lexical_cast<float>(args[1]);
        }
        catch (...) {
        //    _mtx.lock();
            _log->local("Fail parsing max temperature", LOG_ERROR);
         //   _mtx.unlock();

            if (!simpleAnsware(false)) {
          //      _mtx.lock();
                _log->local("Fail sending temp answare.", LOG_ERROR);
          //      _mtx.unlock();
            }
            return;
        }

        try {
            _termo->setMaxTemp(newTemp);
        }
        catch (...) {
            if (!simpleAnsware(false)) {
           //     _mtx.lock();
                _log->local("Fail sending temp answare.", LOG_ERROR);
           //     _mtx.unlock();
            }
            return;
        }
        if (!simpleAnsware(true)) {
           // _mtx.lock();
            _log->local("Fail sending temp answare.", LOG_ERROR);
           // _mtx.unlock();
        }
        return;
    }

  //  _mtx.lock();
    _log->local("Unknown termo request.", LOG_WARNING);
   // _mtx.unlock();

    if (!simpleAnsware(false)) {
       // _mtx.lock();
        _log->local("Fail sending temp answare.", LOG_ERROR);
       // _mtx.unlock();
    }
    return;
}
