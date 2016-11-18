#include "ext.h"
#include <sstream>


namespace ext {


void split_string(const string &str, char sym, vector<string> &out)
{
    bool isFind = false;
    string out1 = "";
    string out2 = "";

    for (const auto &s : str) {
        if (s == sym) {
            isFind = true;
            continue;
        }

        if (!isFind)
            out1 += s;

        if (isFind)
            out2 += s;
    }

    if (!isFind)
        throw string("Split symbol not found.");

    if (out1 == "" || out2 == "")
        throw string("Incorrect string for splitting.");

    out.push_back(out1);
    out.push_back(out2);
}

const string current_datetime()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];

    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

const string ftoa(float num)
{
    ostringstream buff;
    buff << num;
    return buff.str();
}


}
