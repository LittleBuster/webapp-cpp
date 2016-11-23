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


#include "unknownhandler.h"
#include <iostream>


UnknownHandler::UnknownHandler(const shared_ptr<ILog> log): _log(move(log))
{
}

void UnknownHandler::handler(const string &req, const shared_ptr<ITcpClient> &client, mutex &mtx)
{
    string answ = "HTTP/1.1 200 OK\r\n"
                  "Content-Type: application/json; charset=UTF-8\r\n\r\n"
                  "{\"module\": \"404\", \"result\": \"fail\"}";

    try {
        client->send(answ.c_str(), answ.length());
    } catch(const string &err) {
        mtx.lock();
        _log->local("Unknown(H): " + err, LOG_ERROR);
        mtx.unlock();
        return;
    }

    mtx.lock();
    cout << "Unknown request 404." << endl;
    mtx.unlock();
    return;
}
