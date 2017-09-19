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
#include "util.h"
#include "config.h"
#include <unistd.h> // read
#include <string.h> // memcpy
#include <arpa/inet.h> // ntohl

namespace net{



/**
 * 默认分包器，根据首4字节获取包长度
 * data 传入数据
 * size 数据长度
 * start 分包起点
 * end 分包终点
 *
 * 返回值
 * 1 表示有一个完整包
 * -1 表示出错，后续不用继续在这个data上面处理，框架会断开连接
 * -2 表示数据不够一个完整包，先跳过，后续再处理
 **/
int default_spliter(char *data, int size, int &start, int &end)
{
    uint32_t retval = ERR_FD_CONTINUE;
    if (data == NULL)
    {
        LOG_WARN("data is NULL, size:%d, start:%d, end:%d", size, start, end);
        retval = ERR_FD_INVALID;
        return retval;
    }

    if (size < 4)
    {
        LOG_DEBUG("data no enough, size:%d, start:%d, end:%d", size, start, end);
        retval = ERR_FD_CONTINUE;
        return retval;
    }

    uint32_t len = ntohl(*static_cast<uint32_t *>(data+4*start));
    if ((len + start) >= size)
    {
        end = start + len;
        LOG_DEBUG("recv one packet, size:%d, len:%d, start:%d, end:%d", size, len, start, end);
        retval = ERR_FD_ONE_RESULT;
        return retval;
    }
    
    LOG_DEBUG("data no enough, size:%d, start:%d, end:%d", size, start, end);
    return retval;
}



Net::Net(PacketSpliter spliter)
: packet_spliter(spliter)
, max_limit(Config.DEFAULT_MAX_RECV_LIMIT)
{
    int limit = Config.getIntProperty(Config.MAX_RECV_DATA);
    if (limit > 0 && limit < Config.DEFAULT_MAX_MAX_RECV_LIMIT)
    {
        max_limit = limit;
    }
    else if (limit != 0)
    {
        LOG_WARN("invalid custom max recv data limit:%d", limit);
    }

    if (packet_spliter == NULL && default_spliter != NULL)
    {
        LOG_DEBUG("use custom packet spliter:%x", default_spliter);
        packet_spliter = default_spliter;
    }
    else
    {
        LOG_DEBUG("use default packet spliter:%x", spliter);
    }
}


Net::~Net()
{
}


/**
 * 从网络socket中读取完整包，数据存放到data，长度存放到length。
 * 返回值代码读取到的完整包个数。-1为没有，1为有一个完整包，0表示出错，事件层可以关闭此链接
 **/
int Net::readPacket(int fd, char *data, int &lastStart, int &length)
{
	int retval = ERR_FD_CONTINUE;
	if (fd <= -1)
	{
		LOG_ERROR("socket fd is invalid, read packet failed.");
        retval = ERR_FD_INVALID;
		return retval;
	}

    NetBuffer *net_buffer = net_buffer_bluck[fd];
    if (net_buffer == NULL)
    {
        net_buffer = net_alloc();
        if (net_buffer == NULL)
        {
            LOG_ERROR("alloc mem from pool failed, fd:%d", fd);
            retval = ERR_ALLOC_FAILED;
            return retval;
        }
    }
    
	size_t curReadLen = 0;
	size_t totalReadLen = 0;
	while (true)
	{
		curReadLen = read(fd, net_buffer->data, net_buffer->size - totalReadLen);
		if (-1 == curReadLen)
		{
			if(errno == EINTR)
			{
				continue;
			}
			else if(errno == EWOULDBLOCK)
			{
				break;
			}
			else
			{
				LOG_DEBUG("fd: %d, read: -1, error: %s", fd, strerror(errno));
                retval = errno;
				return retval;
			}
		}
		else if(curReadLen == 0)
		{
			LOG_ERROR("fd: %d, socket closed by peer, error: %s", fd, strerror(errno));
			retval = ERR_FD_INVALID;
            return retval;
		}

		// if no enough space, need expand space
		totalReadLen += curReadLen;
		if (curReadLen + lastStart > length)
		{
			LOG_WARN("expand space for fd:%d", fd);
			net_expand(net_buffer);
		}
		memcpy(data + lastStart, net_buffer->data, curReadLen);
		lastStart += curReadLen;
		
	}
}



/**
 * 写包到socket
 * data未待写数据，length代表数据长度
 **/
int Net::writePacket(int fd, const char *data, int length)
{

}


int Net::readPacketLength(int fd)
{
}


};

//size_t packetLen = readPacketLength(fd);
//if (packetLen > max_limit)
//{
//    LOG_ERROR("recv data is too big than:%d, illigle request, close connection, fd:%d", max_limit, fd);
//    return retval;
//}
// alloc mem from pool

