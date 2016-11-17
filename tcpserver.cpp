#include "tcpserver.h"
#include <functional>
#include <thread>


void TcpServer::start(unsigned port, unsigned maxClients)
{
    int retVal;
    struct sockaddr_in sock_addr;

    _sock = socket(AF_INET, SOCK_STREAM, 0);
    if (_sock == INVALID_SOCKET)
        return;

    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = INADDR_ANY;
    sock_addr.sin_port = htons(port);

    retVal = bind(_sock, reinterpret_cast<struct sockaddr *>(&sock_addr), sizeof(sock_addr));
    if (retVal == SOCKET_ERROR)
        return;

    retVal = listen(_sock, maxClients);
    if (retVal == SOCKET_ERROR)
        return;

    for (;;) {
        SOCKET sClient = accept(_sock, NULL, NULL);

        if (sClient == SOCKET_ERROR) {
            acceptError();
            continue;
        }

        auto client = make_shared<TcpClient>(sClient);
        thread th(bind(&TcpServer::newSession, this, client));
        th.detach();
    }
}
