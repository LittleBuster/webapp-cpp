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
    mutex &_mtx;
    const shared_ptr<ITcpClient> _client;
    const shared_ptr<ILog> _log;

public:
    explicit UnknownHandler(const shared_ptr<ITcpClient> &client,
                          const shared_ptr<ILog> log,
                          mutex &mtx);

    void handler(const string &req);
};


#endif
