/**
 * @filedesc: 
 * event_data.h, data
 * @author: 
 *  bbwang
 * @date: 
 *  2017/9/15 12:02:59
 * @modify:
 *
**/

#ifndef __EVENT_DATA_H__
#define __EVENT_DATA_H__
namespace net{


class NetData;
struct EventData {

	// 网络数据
	NetData *net_data;

	// 事件id
	int event_id;
	// 事件类型
	int type;
	// 事件优先级
	int priority;

};


};
#endif

