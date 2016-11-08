#include "tcpserver.h"
#include <functional>
#include <thread>


void TcpServer::start(unsigned port)
{
    try {
        _acpt = make_shared<tcp::acceptor>(_service, tcp::endpoint(tcp::v4(), port));
    }
    catch (...) {
        throw string("Binding ip address and port fail.");
    }
    for (;;) {
        auto sock = make_shared<tcp::socket>(_service);
        try {
            _acpt->accept(*sock);
        }
        catch (...) {
            this->acceptError();
            continue;
        }
        auto client = make_shared<TcpClient>(sock);
        thread th(bind(&TcpServer::newSession, this, client));
        th.detach();
    }
}
