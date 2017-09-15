/**
 * @filedesc: 
 * net.h, handle net data
 * @author: 
 *  bbwang
 * @date: 
 *  2017/9/15 12:02:59
 * @modify:
 *
**/

#ifndef __NET_H__
#define __NET_H__

int (*Spliter)(char *data, int size, int &start, int &end);

class Net {
public:
	Net();
	virtual ~Net();

	/**
	 * 从网络socket中读取完整包，数据存放到data，长度存放到length。
	 * 返回值代码读取到的完整包个数。0为没有，1为有一个完整包，-1表示出错，事件层可以关闭此链接
	 **/
	int readPacket(int fd, char *data, int &length);

	/**
	 * 写包到socket
	 * data未待写数据，length代表数据长度
	 **/
	int writePacket(int fd, const char *data, int length);


private:
	Spliter packet_spliter;
	int fd;
};


#endif

