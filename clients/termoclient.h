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

#ifndef __TERMOCLIENT_H__
#define __TERMOCLIENT_H__

#include "tcpclient.h"


class ITermoClient
{
public:
    virtual void connect(const string &ip, unsigned port)=0;
    virtual void setMaxTemp(float temp)=0;
    virtual float getMaxTemp() const=0;
    virtual void close(void) const=0;
};


class TermoClient: public ITermoClient, private TcpClient
{
public:
    /**
     * Connect to remote server
     * @ip: remote ip address
     * @port: remote socket port
     *
     * throw: error if fail connecting
     */
    void connect(const string &ip, unsigned port);

    /**
     * Sending max temp to server
     * @temp: max temp
     *
     * throw: error if fail sending
     */
    void setMaxTemp(float temp);

    /**
     * Getting max temp from server
     * returns: max temp
     *
     * throw: error if fail sending
     */
    float getMaxTemp() const;

    /*
     * Close connection
     */
    void close(void) const;
};


#endif
