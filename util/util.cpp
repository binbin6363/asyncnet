
#include "util.h"


namespace net{

    

// NetBuffer *net_buffer_bluck[MAX_FD_SIZE];

NetBuffer *net_alloc(size_t len)
{
    if (len <= MEM_MIN_BLOCK)
    {
        len = MEM_MIN_BLOCK;
    }
    else if (len > MEM_MIN_BLOCK && len <= MEM_MID_BLOCK) 
    {
        len = MEM_MID_BLOCK;
    }
    else if (len < MEM_MAX_BLOCK)
    {
        len = PAD(len, 4);
    }
    else 
    {
        LOG_ERROR("[mem] alloc invalid memory block, len:%d", len);
        return NULL;
    }
    NetBuffer *buffer = new NetBuffer(len);
    return buffer;
}


NetBuffer *net_expand(NetBuffer *buffer)
{
}

int net_delloc(NetBuffer *buffer)
{
    delete buffer;
}

int net_reset(NetBuffer *buffer)
{
    if (buffer != NULL)
    {
        buffer->reset();
    }
    else
    {
        LOG_WARN("[mem] reset null pointer!");
    }
    
}


};


