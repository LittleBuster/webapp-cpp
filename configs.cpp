#include "configs.h"
#include <fstream>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>


void Configs::load(const string &filename)
{
    std::ifstream ifs;
    boost::property_tree::ptree pt;

    ifs.open(filename);
    if (!ifs.is_open())
        throw string("File not found.");

    try {
        boost::property_tree::read_json(ifs, pt);
    }
    catch (...) {
        ifs.close();
        throw string("Fail parsing json file.");
    }

    try {
        sc.port = pt.get<unsigned>("Server.Port");
    }
    catch (...) {
        ifs.close();
        throw string("Fail reading configs values.");
    }
    ifs.close();
}
