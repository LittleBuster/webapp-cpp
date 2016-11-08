#ifndef __WEBSERVER_H__
#define __WEBSERVER_H__

#include "tcpserver.h"
#include "log.h"
#include <mutex>


class WebServer final: public TcpServer
{
private:
    mutex _mtx;
    const shared_ptr<ILog> _log;

    string parseRequest(const string &req);

public:
    explicit WebServer(const shared_ptr<ILog> log);

    virtual void newSession(shared_ptr<ITcpClient> client) override final;

    /*
     * Accepting new client error signal
     */
    virtual void acceptError(void) const override final;
};


#endif
