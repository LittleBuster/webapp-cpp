#include "webserver.h"
#include "router.h"
#include "handlers/termohandler.h"
#include "handlers/unknownhandler.h"
#include "clients/termoclient.h"
#include <iostream>


WebServer::WebServer(const shared_ptr<ILog> log, const shared_ptr<IRouter> &router): _log(move(log)),
                                                                                  _router(move(router))
{
}

string WebServer::parseRequest(const string &req)
{
    bool found = false;
    string out = "";

    for (const auto &sym : req) {
        if (sym == ' ') {
            if (!found) {
                found = true;
            }
            else {
                break;
            }
        }

        if (found)
            out += sym;
    }
    return out;
}


void WebServer::newSession(shared_ptr<ITcpClient> client)
{
    char data[1024];
    string req = "";

    try {
        client->recv(data, 1024);
    }
    catch (const string &err) {
        cout << err << endl;
        return;
    }

    req = parseRequest(string(data));
    _router->navigate(req, client, _mtx);
}

void WebServer::acceptError() const
{
    cout << "Accepting error" << endl;
}
