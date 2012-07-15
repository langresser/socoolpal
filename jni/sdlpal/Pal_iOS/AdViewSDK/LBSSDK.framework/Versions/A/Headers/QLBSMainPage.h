//
//  QLBSService.h
//  qqlbsSDK
//
//  Created by ease lin on 7/11/11.
//  Copyright 2011 Tencent. All rights reserved.
//

/**
 *	@mainpage API大致调用流程
 *		@details 
 *		@ref 
 *		QLBSLocationManager 是定位工具对象类，该类主要提供其它第三方单单只需要定位插件接口
 *		QLBSService 类似一个服务请求载体（内部包含了定位接口QLBSLocationManager以及LBS服务请求），服务请求和派发通过iOS的消息派发中心 NSNotificationCenter 运作
 *		- 首先任何需要 @ref QLBSService 提供服务的，需要设置用户名和密码，并且需要在 NSNotificationCenter 消息中心注册相应类型的服务，并提供回调函数
 *			@code - (void)setUsrName:(NSString *)name password:(NSString*)pass @endcode
 *			@code [[NSNotificationCenter defaultCenter] addObserver:usr selector:aSelector name:aServiceName object:nil] @endcode
 *			服务类型包括但不限于以下几种: @ref QLBSSERVICE_LOCATE | @ref QLBSSERVICE_GETCURRPOSITION
 *		- 然后通过 @ref QLBSService 提供的请求函数请求相应的服务数据，请求函数包括但不限于以下几种:
 *			@code - (BOOL)startLocate @endcode
 *			@code - (BOOL)requestGetCurrentPosition:(int)reqid @endcode
 *		- @ref QLBSService 获取到相应的服务内容后，通过之前注册的回调函数通知请求者，回调函数原型为:
 *			@code -(void)callback:(NSNotification*)call (callback可以是任意名字) @endcode
 *			回调函数中参数 (NSNotification*)call 包含了服务的请求结果 @ref QLBSServiceMsg (存在于 NSNotification 对象的 userInfo 中，KEY值为 @ref SERVICE_MSG_KEY)
 *		- 假如API的用法有任何不明白的地方，可以找easelin ：）
 *		- 版本更新记录: \n
 *			v1.3 \n
 *			添加了两个定位属性接口 sysLocateAccuracy & sysLocateTimeOut \n
 *			v1.4 \n
 *			添加错误码 @ref kQLBSServiceLocateErr & @ref kQLBSServiceLocateTimeOutErr \n
 *			添加接口 @code - (BOOL)isPlatformSupport:(double)lat longitude:(double)log @endcode
 *			添加接口 @code - (NSData*)exportPlatformDeviceData @endcode
 *			v1.5 \n
 *			添加错误码 @ref kQLBSServiceLocatePermissionErr \n
 *			移除所有GoogleMap的定位方式以及接口 \n
 *			v1.5.1 \n
 *			添加接口 @code - (BOOL)isAbleLocate @endcode
 *			v1.5.2 \n
 *			添加接口 @code - (NSData*)exportPlatformDeviceData:(double)lat longitude:(double)log @endcode
 */
