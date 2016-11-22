/* Webapp test application
 *
 * Copyright (C) 2016 Sergey Denisov.
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public Licence 3
 * as published by the Free Software Foundation; either version 3
 * of the Licence, or (at your option) any later version.
 */

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

    /*
     * New client connected
     */
    virtual void newSession(shared_ptr<ITcpClient> client) override final;

    /*
     * Accepting new client error signal
     */
    virtual void acceptError(void) const override final;
};


#endif
