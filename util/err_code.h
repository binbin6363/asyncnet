/**
 * @filedesc: 
 * err_code.h, error code
 * @author: 
 *  bbwang
 * @date: 
 *  2017/9/15 12:02:59
 * @modify:
 *
**/

#ifndef __NET_ERR_CODE_H__
#define __NET_ERR_CODE_H__

namespace net{

const static int ERR_ALLOC_FAILED                   = -5;   // alloc memory failed
const static int ERR_FD_READ_FAILED                 = -4;   // fd read failed
const static int ERR_FD_WRITE_FAILED                = -3;   // fd write failed
const static int ERR_FD_CONTINUE                    = -2;   // need continue
const static int ERR_FD_INVALID                     = -1;   // invalid file description
const static int ERR_FD_ONE_RESULT                  = 1;    // get one result


const static unsigned int ERR_OK                    = 0;    // ok

};

#endif

