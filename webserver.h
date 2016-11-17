#ifndef __WEBSERVER_H__
#define __WEBSERVER_H__

#include "tcpserver.h"
#include "router.h"
#include "log.h"
#include <mutex>


class WebServer final: public TcpServer
{
private:
    mutex _mtx;
    const shared_ptr<ILog> _log;
    const shared_ptr<IRouter> _router;

    string parseRequest(const string &req);

public:
    explicit WebServer(const shared_ptr<ILog> log, const shared_ptr<IRouter> &router);

    virtual void newSession(shared_ptr<ITcpClient> client) override final;

    /*
     * Accepting new client error signal
     */
    virtual void acceptError(void) const override final;
};


#endif
