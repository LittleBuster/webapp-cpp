#include "unknownhandler.h"
#include <iostream>
#include <boost/lexical_cast.hpp>


UnknownHandler::UnknownHandler(const shared_ptr<ILog> log): _log(move(log))
{
}

void UnknownHandler::handler(const string &req)
{
    string answ = "HTTP/1.1 200 OK\r\n"
                  "Content-Type: application/json; charset=UTF-8\r\n\r\n"
                  "{\"module\": \"404\", \"result\": \"fail\"}";

    try {
        //_client->send(answ.c_str(), answ.length());
    } catch(const string &err) {
       // _mtx.lock();
        _log->local("Unknown(H): " + err, LOG_ERROR);
     //   _mtx.unlock();
        return;
    }

   // _mtx.lock();
    cout << "Unknown request 404." << endl;
   // _mtx.unlock();
    return;
}
