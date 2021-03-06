/**
 * @filedesc: 
 * request.h, data
 * @author: 
 *  bbwang
 * @date: 
 *  2017/9/15 12:02:59
 * @modify:
 *
**/

#ifndef __REQUEST_H__
#define __REQUEST_H__

struct Request {

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

};

#endif

