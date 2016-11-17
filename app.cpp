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
