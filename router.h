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

    /**
     * Adding new handler
     * @name: name of handler
     * @module: new handler
     */
    void addModule(const string &name, const shared_ptr<IHandler> &module);

    /**
     * Checking handler exists
     * @name: name of handler
     *
     * returns true: if handler exists
     * returns false: if handler not found
     */
    bool checkModuleExists(const string &name);

public:
    explicit Router(const shared_ptr<IHandler> &termo, const shared_ptr<IHandler> &unknown);

    /**
     * Call one of handlers
     * @request: string request from client
     * @client: connected tcp client
     * @mtx: server thread mutext
     *
     * returns false: if fail parsing request or module not found
     * returns true: if ok
     */
    bool navigate(const string &request, const shared_ptr<ITcpClient> &client, mutex &mtx);
};


#endif
