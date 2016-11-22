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
