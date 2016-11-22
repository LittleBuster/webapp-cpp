/* Webapp test application
 *
 * Copyright (C) 2016 Sergey Denisov.
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public Licence 3
 * as published by the Free Software Foundation; either version 3
 * of the Licence, or (at your option) any later version.
 */


#include "termohandler.h"
#include "ext.h"
#include "configs.h"
#include <iostream>


TermoHandler::TermoHandler(const shared_ptr<IConfigs> &cfg, const shared_ptr<ILog> log):
    _cfg(move(cfg)), _log(move(log))
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
    tuple<string, string> args;
    const auto &hsc = _cfg->getHouseCfg();
    shared_ptr<ITermoClient> termo = make_shared<TermoClient>();

    if (req == "get_temp") {
        float mt;

        try {
            termo->connect(hsc.ip, hsc.port);
            mt = termo->getMaxTemp();
            termo->close();
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
        args = ext::split_string(req, '=');
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

    if (get<0>(args) == "temp_set") {
        float newTemp;

        try {
            newTemp = atof(get<1>(args).c_str());
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
            termo->connect(hsc.ip, hsc.port);
            termo->setMaxTemp(newTemp);
            termo->close();
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
