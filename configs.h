#ifndef __CONFIGS_H__
#define __CONFIGS_H__

#include <memory>

using namespace std;


typedef struct {
    unsigned port;
} ServerCfg;


class IConfigs
{
public:
    virtual const ServerCfg& getServerCfg(void) const = 0;
    virtual void load(const string &filename) = 0;
};


class Configs: public IConfigs
{
private:
    ServerCfg sc;

    string readString(ifstream &is) const;

    int readInt(ifstream &is) const;

public:
    inline const ServerCfg& getServerCfg(void) const { return sc; }

    /**
     * Loading configs from json file
     * @filename: name of json file
     *
     * throw: errror if file not found or parsing fail
     */
    void load(const string &filename);
};


#endif
