#include "unknownhandler.h"
#include <iostream>
#include <boost/lexical_cast.hpp>


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
