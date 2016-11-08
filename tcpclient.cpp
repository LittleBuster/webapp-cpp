#include "tcpclient.h"
#include <stdlib.h>
#include <boost/lexical_cast.hpp>


TcpClient::TcpClient()
{
    _client = make_shared<tcp::socket>(_service);
}

TcpClient::TcpClient(const shared_ptr<tcp::socket> &parent_client)
{
    _client = parent_client;
}

void TcpClient::connect(const string &ip, unsigned port)
{
    boost::system::error_code err;

    tcp::resolver resolver(_service);
    boost::asio::connect(*_client, resolver.resolve({ip, boost::lexical_cast<string>(port)}), err);
    if (err)
        throw string("Can not connect to server.");
}

void TcpClient::send(const void *data, size_t len) const
{
    boost::system::error_code error;

    _client->write_some(boost::asio::buffer(data, len), error);
    if (error)
        throw string("Fail sending data.");
}

void TcpClient::recv(void *data, size_t len) const
{
    boost::system::error_code error;

    _client->read_some(boost::asio::buffer(data, len), error);
    if (error == boost::asio::error::eof)
        return;
    else if (error)
        throw string("Fail receiving data.");
}

void TcpClient::close() const
{
    _client->close();
}
