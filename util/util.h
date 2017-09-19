/**
 * @filedesc: 
 * util.h, handle net data
 * @author: 
 *  bbwang
 * @date: 
 *  2017/9/15 12:02:59
 * @modify:
 *
**/

#ifndef __NET_UTIL_H__
#define __NET_UTIL_H__

namespace net{

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(pointer) if (pointer != NULL) {delete pointer; pointer = NULL;}
#endif

#ifndef PAD
#define PAD(num, pad) (num - (num % pad) + pad)
#endif



#pragma pack(4)

struct NetBuffer {
	char *data;
	unsigned int size;
    unsigned int len;
    static unsigned int calc = 0;

    NetBuffer(int cap)
        : data(NULL)
        , size(cap)
        , len(0)
    {
        // here can use mem pool
        data = (char *)malloc(size * sizeof(char));

        if (data != NULL)
        {
            memset(data, 0, size);
            LOG_DEBUG("[mem] alloc net buffer len:%d, mem addr:%p", size, data);
        }
        else
        {
            LOG_ERROR("[mem] alloc net buffer failed, len:%d", size);
        }

    }

    ~NetBuffer()
    {
        SAFE_DELETE(data);
        size = 0;
        len = 0;
    }

    int reset()
    {
        memset(data, 0, size);
        len = 0;
    }
};

#pragma pack()



static const int MAX_FD_SIZE   = 65535;
static const int MEM_MIN_BLOCK = 2048;       // 2KB
static const int MEM_MID_BLOCK = 4096;       // 4KB
static const int MEM_MAX_BLOCK = 10485760;   // 10MB

NetBuffer *net_buffer_bluck[MAX_FD_SIZE];



NetBuffer *net_alloc(size_t len = MEM_MIN_BLOCK);

NetBuffer *net_expand(NetBuffer *buffer);

int net_delloc(NetBuffer *buffer);

int net_reset(NetBuffer *buffer);

#ifdef __cplusplus
}
#endif

};
#endif

