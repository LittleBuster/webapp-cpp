#ifndef __TERMO_HANDLER_H__
#define __TERMO_HANDLER_H__

#include "ihandler.h"
#include "clients/termoclient.h"
#include "tcpclient.h"
#include "log.h"
#include <memory>
#include <vector>

using namespace std;


class TermoHandler: public IHandler
{
private:
    const shared_ptr<ITermoClient> _termo;
    const shared_ptr<ILog> _log;

    bool simpleAnsware(bool result);

    bool tempAnsware(float temp);

    vector<string> parseRequest(const string &req);

public:
    explicit TermoHandler(const shared_ptr<ITermoClient> &termo,
                          const shared_ptr<ILog> log);

    void handler(const string &req);
};


#endif
