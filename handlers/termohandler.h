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

    void simpleAnsware(bool result, const shared_ptr<ITcpClient> &client);

    void tempAnsware(float temp, const shared_ptr<ITcpClient> &client);

    vector<string> parseRequest(const string &req);

public:
    explicit TermoHandler(const shared_ptr<IConfigs> &cfg, const shared_ptr<ILog> log);

    void handler(const string &req, const shared_ptr<ITcpClient> &client, mutex &mtx);
};


#endif
