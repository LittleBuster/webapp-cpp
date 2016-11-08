#ifndef __IHANDLER_H__
#define __IHANDLER_H__

#include <string>

using namespace std;


class IHandler
{
public:
    virtual void handler(const string &req) = 0;
};


#endif
