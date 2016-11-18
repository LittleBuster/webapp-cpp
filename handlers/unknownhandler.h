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

    void handler(const string &req, const shared_ptr<ITcpClient> &client, mutex &mtx);
};


#endif
