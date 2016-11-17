#include <memory>
#include "app.h"
#include "webserver.h"
#include "log.h"
#include "configs.h"
#include "handlers/termohandler.h"
#include "handlers/unknownhandler.h"
#include "clients/termoclient.h"
#include "router.h"


int main(void)
{
    auto log = make_shared<Log>();
    auto cfg = make_shared<Configs>();    
    auto termoClient = make_shared<TermoClient>();
    auto termoHandler = make_shared<TermoHandler>(termoClient, log);
    auto unknownHandler = make_shared<UnknownHandler>(log);
    auto router = make_shared<Router>(termoHandler, unknownHandler);
    auto wserver = make_shared<WebServer>(log, router);
    auto app = make_shared<App>(wserver, cfg, log);

    return app->start();
}
