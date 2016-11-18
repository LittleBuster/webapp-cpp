#include "router.h"
#include "ext.h"
#include <functional>
#include <vector>
#include <iostream>


void Router::addModule(const string &name, const shared_ptr<IHandler> &module)
{
    _reqs.insert(make_pair(name, module));
    _modules.push_back(name);
}

bool Router::checkModuleExists(const string &name)
{
    for (const auto &module : _modules)
        if (name == module)
            return true;
    return false;
}

Router::Router(const shared_ptr<IHandler> &termo, const shared_ptr<IHandler> &unknown)
{
    addModule("termo", termo);
    addModule("unknown", unknown);
}

bool Router::navigate(const string &request, const shared_ptr<ITcpClient> &client, mutex &mtx)
{
    vector<string> first;
    vector<string> res;

    try {
        ext::split_string(request, '/', first);
        ext::split_string(first[1], '?', res);
    }
    catch (...) {
        _reqs["unknown"]->handler("", client, mtx);
        return false;
    }

    if (!checkModuleExists(res[0])) {
        _reqs["unknown"]->handler("", client, mtx);
        return false;
    }

    _reqs[res[0]]->handler(res[1], client, mtx);
    return true;
}
