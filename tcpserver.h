#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__

#include <memory>
#include <thread>
#include "tcpclient.h"
#include <boost/bind.hpp>
#include <boost/asio.hpp>

using namespace std;
using boost::asio::ip::tcp;


class ITcpServer
{
public:
    virtual void newSession(shared_ptr<ITcpClient> client) = 0;
    virtual void acceptError(void) const = 0;
    virtual void start(unsigned port) = 0;
};


class TcpServer: public ITcpServer
{
private:
    boost::asio::io_service _service;
    shared_ptr<tcp::acceptor> _acpt;

public:
    /*
     * New client connection session
     */
    virtual void newSession(shared_ptr<ITcpClient> client) { };

    /*
     * Accepting new client error signal
     */
    virtual void acceptError(void) const { };

    /**
     * Binding tcp server
     * @port: local tcp port
     *
     * throw: error if fail binding
     */
    void start(unsigned port);
};


#endif
