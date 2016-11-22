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

#ifndef __UNKNOWN_HANDLER_H__
#define __UNKNOWN_HANDLER_H__

#include "ihandler.h"
#include "tcpclient.h"
#include "log.h"
#include <memory>
#include <mutex>

using namespace std;


class UnknownHandler: public IHandler
{
private:
    const shared_ptr<ILog> _log;

public:
    explicit UnknownHandler(const shared_ptr<ILog> log);

    /**
     * Unknown handler
     * @req: string of request
     * @client: connected tcp client
     * @mtx: server mutex
     */
    void handler(const string &req, const shared_ptr<ITcpClient> &client, mutex &mtx);
};


#endif
