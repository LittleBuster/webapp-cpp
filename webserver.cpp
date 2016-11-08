#include "webserver.h"
#include "router.h"
#include "handlers/termohandler.h"
#include "handlers/unknownhandler.h"
#include "clients/termoclient.h"
#include <iostream>


WebServer::WebServer(const shared_ptr<ILog> log): _log(move(log))
{
}

string WebServer::parseRequest(const string &req)
{
    bool found = false;
    string out = "";

    for (size_t i = 0; i < req.size(); i++) {
        if (req[i] == ' ')
            if (!found)
                found = true;
            else
                break;

        if (found)
            out += req[i];
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

    auto termoClient = make_shared<TermoClient>();
    auto termoHandler = make_shared<TermoHandler>(termoClient, client, _log, _mtx);
    auto unknownHandler = make_shared<UnknownHandler>(client, _log, _mtx);
    auto router = make_shared<Router>(termoHandler, unknownHandler);

    req = parseRequest(string(data));

    router->navigate(req);
}

void WebServer::acceptError() const
{
    cout << "Accepting error" << endl;
}
