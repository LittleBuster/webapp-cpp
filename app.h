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

#ifndef __APP_H__
#define __APP_H__

#include "webserver.h"
#include "tcpserver.h"
#include "log.h"
#include "configs.h"
#include <memory>

using namespace std;


class App
{
private:
    const shared_ptr<ITcpServer> _wserver;
    const shared_ptr<IConfigs> _cfg;
    const shared_ptr<ILog> _log;

public:
    explicit App(const shared_ptr<ITcpServer> &wserver, const shared_ptr<IConfigs> &cfg, const shared_ptr<ILog> &log);

    /*
     * Starting application
     */
    int start();
};


#endif
