/**
 * @filedesc: 
 * config.cpp
 * @author: 
 *  bbwang
 * @date: 
 *  2017/9/15 12:02:59
 * @modify:
 *
**/

#include "config.h"

namespace net{

Config::map<string, string> properties;


int Config::getIntProperty(const char *key, int default_value)
{
}

const char *Config::getStringProperty(const char *key, const char *default_value)
{
}

bool Config::getBoolProperty(const char *key, bool default_value)
{
}

};


