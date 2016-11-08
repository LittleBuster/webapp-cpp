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

    int start();
};


#endif
