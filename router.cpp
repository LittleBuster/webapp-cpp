#include "router.h"
#include <functional>
#include <vector>
#include <iostream>
#include <boost/algorithm/string.hpp>


Router::Router(const shared_ptr<IHandler> &termo, const shared_ptr<IHandler> &unknown)
{
    _reqs.insert(make_pair("termo", termo));
    _reqs.insert(make_pair("unknown", unknown));
}

bool Router::navigate(const string &request)
{
    vector<string> first;
    vector<string> res;

    try {
        boost::split(first, request, boost::is_any_of("/"));
        if (first.size() <= 1) {
            _reqs["unknown"]->handler("");
            return false;
        }
        boost::split(res, first[1], boost::is_any_of("?"));
        if (res.size() <= 1) {
            _reqs["unknown"]->handler("");
            return false;
        }
    }
    catch (...) {
        _reqs["unknown"]->handler("");
        return false;
    }

    _reqs[res[0]]->handler(res[1]);
    return true;
}
