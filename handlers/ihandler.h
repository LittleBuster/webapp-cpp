#ifndef __IHANDLER_H__
#define __IHANDLER_H__

#include <string>
#include "tcpclient.h"
#include <mutex>

using namespace std;


class IHandler
{
public:
    virtual void handler(const string &req, const shared_ptr<ITcpClient> &client, mutex &mtx) = 0;
};


#endif
