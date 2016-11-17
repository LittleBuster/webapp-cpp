#ifndef __ROUTER_H__
#define __ROUTER_H__

#include "tcpclient.h"
#include "handlers/ihandler.h"
#include <memory>
#include <map>
#include <mutex>
#include <vector>

using namespace std;


class IRouter
{
public:
    virtual bool navigate(const string &request, const shared_ptr<ITcpClient> &client, mutex &mtx)=0;
};


class Router: public IRouter
{
private:
    vector<string> _modules;
    map<string, shared_ptr<IHandler>> _reqs;

    void addModule(const string &name, const shared_ptr<IHandler> &module);

    bool checkModuleExists(const string &name);

public:
    explicit Router(const shared_ptr<IHandler> &termo, const shared_ptr<IHandler> &unknown);

    bool navigate(const string &request, const shared_ptr<ITcpClient> &client, mutex &mtx);
};


#endif
