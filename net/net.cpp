/**
 * @filedesc: 
 * net.cpp, handle net data
 * @author: 
 *  bbwang
 * @date: 
 *  2017/9/15 12:02:59
 * @modify:
 *
**/

#include "net.h"
#include <unistd.h>


/**
 * 从网络socket中读取完整包，数据存放到data，长度存放到length。
 * 返回值代码读取到的完整包个数。0为没有，1为有一个完整包，-1表示出错，事件层可以关闭此链接
 **/
int Net::readPacket(int fd, char *data, int &length)
{
	int retval = 0;
	if (fd == -1)
	{
		LOG_ERROR("socket fd is invalid, read packet failed.");
		retval = -1;
		return retval;
	}

	char *buffer = bufferPool->get(fd);
	int len = read(fd, buffer, buflen);
}



/**
 * 写包到socket
 * data未待写数据，length代表数据长度
 **/
int Net::writePacket(int fd, const char *data, int length)
{

}


