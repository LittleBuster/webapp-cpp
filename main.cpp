#include <memory>
#include "app.h"
#include "webserver.h"
#include "log.h"
#include "configs.h"


int main(void)
{
    auto log = make_shared<Log>();
    auto cfg = make_shared<Configs>();
    auto wserver = make_shared<WebServer>(log);
    auto app = make_shared<App>(wserver, cfg, log);

    return app->start();
}
