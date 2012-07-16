/*
 *  QLBSServiceDefine.h
 *  LBSSDK
 *
 *  Created by easelin on 11-8-3.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _QLBSSERVICE_DEFINE_H_
#define _QLBSSERVICE_DEFINE_H_

/** @brief 服务错误码 */
enum {
	kQLBSServiceNoneErr = 0,				/**<  无错误 */
	//定位错误码
	kQLBSServiceLocatePermissionErr = 1,	/**<  定位出错(一般由于未打开定位服务) */
	kQLBSServiceLocateErr = 10,				/**<  定位出错(一般原因) */
	kQLBSServiceLocateTimeOutErr = 11,		/**<  定位超时(一般情况是由于定位时间太长) */
	//定位平台错误码
	kQLBSServiceExceptionErr = 101,			/**<  系统异常 */
	kQLBSServicePositionFailErr = 102,		/**<  系统无法根据输入定位 */
	kQLBSServiceInputErr = 202,				/**<  输入条件不足 */
	kQLBSServiceBackTimeOutErr = 301,		/**<  后端Server超时,如AddressServer */
	//下面两个为统一的网络出错码
	kQLBSServiceNetConnectionErr = 10001,	/**<  连接出错(网络不可连接) */
	kQLBSServiceNetTimeOutErr = 10002,		/**<  连接超时 */
};

/** @brief POI排序方式 */
typedef enum
{
	kSORT_BY_DISTANCE = 0, /**<  按距离排序 */
	kSORT_BY_HOT      = 1  /**<  按热度排序 */
} QLBSPoiSortMode;

/** @brief 服务消息 ServiceMsg 所在的KEY */
extern NSString* const SERVICE_MSG_KEY;

/** @brief 定位当前GPS等信息 */
extern NSString* const QLBSSERVICE_LOCATE;
/** @brief 获取当前位置信息 */
extern NSString* const QLBSSERVICE_GETCURRPOSITION;
/** @brief 获取附近POI列表 */
extern NSString* const QLBSSERVICE_GETNEARPOILIST;
/** @brief 搜索附近POI */
extern NSString* const QLBSSERVICE_SEARCHNEARPOILIST;

///** @brief 系统定位的方式 */
//typedef enum
//{
//    kLOCATE_BY_MKV = 0, /**<  通过GoogleMap定位 */
//    kLOCATE_BY_CLM = 1, /**<  通过Apple系统定位 */
//} QLBSSysLocateWay;

#endif