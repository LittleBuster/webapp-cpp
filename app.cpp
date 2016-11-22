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


#include "app.h"
#include <iostream>


App::App(const shared_ptr<ITcpServer> &wserver, const shared_ptr<IConfigs> &cfg,
         const shared_ptr<ILog> &log):
        _wserver(move(wserver)), _cfg(move(cfg)), _log(move(log))
{
}

int App::start()
{
    _log->setLogFile("wserver.log");

    try {
        _cfg->load("wserver.cfg");
    }
    catch (...) {
        _log->local("Fail loading configs.", LOG_ERROR);
        return -1;
    }

    const auto &sc = _cfg->getServerCfg();

    cout << "Starting WebServer..." << endl;
    try {
        _wserver->start(sc.port, 200);
    }
    catch (...) {
        _log->local("Fail binding WebServer!", LOG_ERROR);
        return -1;
    }

    return 0;
}
