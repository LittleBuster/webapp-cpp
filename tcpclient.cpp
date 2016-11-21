#include "tcpclient.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>


TcpClient::TcpClient()
{
}

TcpClient::TcpClient(SOCKET sock)
{
    _client = sock;
}

void TcpClient::connect(const string &ip, unsigned port)
{
    int retVal;
    struct sockaddr_in sock_addr;

    memset(&sock_addr, 0x00, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = inet_addr(ip.c_str());
    sock_addr.sin_port = htons(port);

    _client = socket(AF_INET, SOCK_STREAM, 0);
    if (_client == INVALID_SOCKET)
        throw string("Can not create client socket.");

    retVal = ::connect(_client, reinterpret_cast<struct sockaddr *>(&sock_addr), sizeof(sock_addr));
    if (retVal == SOCKET_ERROR)
        throw string("Can not connect to server.");
}

void TcpClient::send(const void *data, size_t len) const
{
    int retVal = 0;

    for (;;) {
        retVal = ::send(_client, data, len, MSG_NOSIGNAL);
        if (retVal == SOCKET_ERROR)
            throw string("Fail sending data.");

        if (retVal == static_cast<int>(len))
            break;
    }
}

void TcpClient::recv(void *data, size_t len) const
{
    size_t bytes;

    bytes = ::recv(_client, data, len, MSG_NOSIGNAL);
    if ((bytes == 0) || (bytes == SOCKET_ERROR))
        throw string("Fail receiving data.");
}

void TcpClient::close() const
{
    if (_client != INVALID_SOCKET) {
        ::shutdown(_client, 1);
        ::close(_client);
    }
}
