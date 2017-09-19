/**
 * @filedesc: 
 * net_data.h, data
 * @author: 
 *  bbwang
 * @date: 
 *  2017/9/15 12:02:59
 * @modify:
 *
**/

#ifndef __NET_DATA_H__
#define __NET_DATA_H__

namespace net{

struct NetData {

	// 网络数据上的文件描述符
	int fd;
	// 网络数据指针
	char *data;
	// 网络数据大小
	int size;
	// 网络数据类型
	int type;
	// 网络数据优先级
	int priority;
	// 网络数据首次接收时间
	int recv_time;
	// 网络数据有效期，过期丢弃
	int expire;

};

};
#endif

