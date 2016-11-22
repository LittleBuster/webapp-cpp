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
    tuple<string, string> first, second;

    try {
        first = ext::split_string(request, '/');
        second = ext::split_string(get<1>(first), '?');
    }
    catch (...) {
        _reqs["unknown"]->handler("", client, mtx);
        return false;
    }

    if (!checkModuleExists(get<0>(second))) {
        _reqs["unknown"]->handler("", client, mtx);
        return false;
    }

    _reqs[get<0>(second)]->handler(get<1>(second), client, mtx);
    return true;
}
