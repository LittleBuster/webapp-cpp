#ifndef __ROUTER_H__
#define __ROUTER_H__

#include "handlers/ihandler.h"
#include "handlers/termohandler.h"
#include "handlers/unknownhandler.h"
#include <memory>
#include <map>

using namespace std;


class IRouter
{
public:
    virtual bool navigate(const string &request) = 0;
};


class Router: public IRouter
{
private:
    map<string, shared_ptr<IHandler>> _reqs;

public:
    explicit Router(const shared_ptr<IHandler> &termo, const shared_ptr<IHandler> &unknown);

    bool navigate(const string &request);
};


#endif
