/**
 * @filedesc: 
 * config.h, handle net data
 * @author: 
 *  bbwang
 * @date: 
 *  2017/9/15 12:02:59
 * @modify:
 *
**/

#ifndef __NET_CONFIG_H__
#define __NET_CONFIG_H__

#include <map>
#include <string>
using namespace std;

namespace net{

struct Config
{
	static int getIntProperty(const char *key, int default_value);

	static int getStringProperty(const char *key, const char *default_value);

	static int getBoolProperty(const char *key, const char *default_value);


private:
	static map<string, string> properties;

public:
	static const char *MAX_RECV_DATA = "max_recv_limit";
    static unsigned int DEFAULT_MAX_RECV_LIMIT = (1024 * 1024 * 1);
    static unsigned int DEFAULT_MAX_MAX_RECV_LIMIT = (1024 * 1024 * 1024);
};


};

#endif

