#include "configs.h"
#include <fstream>
#include <iostream>


string Configs::readString(ifstream &is) const
{
    char line[255];
    bool isFind = false;
    string out = "";

    while (1) {
        is.getline(line, 255);
        if (line[0] != '#' || line[0] != '/' || line[0] != '\n')
            break;
    }

    for (const auto &sym : line) {
        if (sym == '=') {
            isFind = true;
            continue;
        }
        if (isFind && sym != ' ')
            out += sym;
    }
    return out;
}

int Configs::readInt(ifstream &is) const
{
    char line[255];
    bool isFind = false;
    string out = "";

    while (1) {
        is.getline(line, 255);
        if (line[0] != '#' || line[0] != '/' || line[0] != '\n')
            break;
    }

    for (const auto &sym : line) {
        if (sym == '=') {
            isFind = true;
            continue;
        }
        if (isFind && sym != ' ')
            out += sym;
    }
    return atoi(out.c_str());
}


void Configs::load(const string &filename)
{
    ifstream ifs;

    ifs.open(filename);
    if (!ifs.is_open())
        throw string("File not found.");

    try {
        sc.port = static_cast<unsigned>(readInt(ifs));
        hsc.ip = readString(ifs);
        hsc.port = static_cast<unsigned>(readInt(ifs));
    }
    catch (...) {
        ifs.close();
        throw string("Fail reading configs values.");
    }
    ifs.close();
}
