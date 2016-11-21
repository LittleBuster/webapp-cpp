#ifndef __TERMOCLIENT_H__
#define __TERMOCLIENT_H__

#include "tcpclient.h"


class ITermoClient
{
public:
    virtual void connect(const string &ip, unsigned port)=0;
    virtual void setMaxTemp(float temp)=0;
    virtual float getMaxTemp() const=0;
    virtual void close(void) const= 0;
};


class TermoClient: public ITermoClient, public TcpClient
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
