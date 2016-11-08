#ifndef __TERMOCLIENT_H__
#define __TERMOCLIENT_H__


class ITermoClient
{
public:
    virtual void setMaxTemp(float temp) = 0;
    virtual float getMaxTemp() = 0;
};


class TermoClient: public ITermoClient
{
public:
    explicit TermoClient();

    void setMaxTemp(float temp);

    float getMaxTemp();
};


#endif
