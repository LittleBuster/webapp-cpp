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

#ifndef __TERMO_HANDLER_H__
#define __TERMO_HANDLER_H__

#include "ihandler.h"
#include "clients/termoclient.h"
#include "tcpclient.h"
#include "configs.h"
#include "log.h"
#include <memory>
#include <vector>

using namespace std;


class TermoHandler: public IHandler
{
private:
    const shared_ptr<IConfigs> _cfg;
    const shared_ptr<ILog> _log;    

    /**
     * Sending ok/fail answare to client
     * @result: type of wnsware
     * @client: connected tcp client
     *
     * throw: error if sending faile
     */
    void simpleAnsware(bool result, const shared_ptr<ITcpClient> &client);

    /**
     * Sending answare with max temperature to client
     * @temp: max temperature
     * @client: connected tcp client
     *
     * throw: error if sending faile
     */
    void tempAnsware(float temp, const shared_ptr<ITcpClient> &client);

public:
    explicit TermoHandler(const shared_ptr<IConfigs> &cfg, const shared_ptr<ILog> log);

    /**
     * Termo handler
     * @req: string of request
     * @client: connected tcp client
     * @mtx: server mutex
     */
    void handler(const string &req, const shared_ptr<ITcpClient> &client, mutex &mtx);
};


#endif
