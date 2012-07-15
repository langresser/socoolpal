//
//  QLBSService.h
//  qqlbsSDK
//
//  Created by ease lin on 7/11/11.
//  Copyright 2011 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "QLBSServiceData.h"
#import "QLBSServiceDefine.h"

/**
 *	@brief 服务请求载体
 *	@note 请求服务流程:
 *	- 外面使用者在调用业务接口前需要先在NSNotificationCenter注册下面的服务名字:
 *		@code [[NSNotificationCenter defaultCenter] addObserver:usr selector:aSelector name:aServiceName object:nil] @endcode
 *		aSelector为usr的回调方法(回调会在主线程，所以不必当心回调改变UI的情况): -(void)callback:(NSNotification*)call，call对象的userInfo将会包含一个key为 @ref SERVICE_MSG_KEY 的QLBSServiceMsg对象，这个对象包含了对于请求的reqid，服务结果等信息
 *	- 当usr被释放时记得调用注销服务函数:
 *		@code [[NSNotificationCenter defaultCenter] removeObserver:usr name:aServiceName object:nil] @endcode
 */
@interface QLBSService : NSObject

/** 
 *	@brief 获得该类的单子对象
 *	@return 返回全局单子对象指针
 */
+ (QLBSService*)sharedService;

/** 
 *	@brief 设置由LBS定位平台分配的API接口用户名和密码
 *	@note 该值不设置，不发送网络请求
 *	@param[in] name LBS定位平台分配的用户名
 *	@param[in] pass LBS定位平台分配的密码
 */
- (void)setUsrName:(NSString *)name password:(NSString*)pass;

/**
 *	@brief 系统的定位精度
 *	@note 默认为kCLLocationAccuracyHundredMeters，请勿将该值设置到很高精度，比如kCLLocationAccuracyBest，因为一般情况下面没法到达该精度的要求，会在超时时间过后返回一个精度最高的值
 */
@property (nonatomic, assign) CLLocationAccuracy sysLocateAccuracy;

/**
 *	@brief 系统的定位超时时间
 *	@note 默认为10s，假如在超时时间内，系统还未找到符合sysLocateAccuracy精度的要求，将在该超时时间后返回一个精度最高的值(假如有的话)
 */
@property (nonatomic, assign) NSTimeInterval sysLocateTimeOut;


/**
 *	@brief 网络超时时间
 *	@note 默认10s
 */
@property (nonatomic, assign) NSTimeInterval networkTimeOut;
/** 
 *	@brief 设置当前的用户QQ号 
 *	@note 用于保护用户和定位平台的安全，不带容易造成定位平台的误杀
 */
@property (nonatomic, assign) uint64_t currentUIN;
/** 
 *	@brief 当前的系统获取的GPS位置信息
 *	@note 调用startLocate后更新，初始值nil
 */
@property (nonatomic, readonly, retain) CLLocation* currLocation;
/** 
 *	@brief 是否正在刷新当前GPS位置信息 
 *	@note 内部已做判断，这个值只是给外面知道
 */
@property (nonatomic, readonly) BOOL isUpdatingLocation;
/**
 *	@brief 开始定位当前的GPS信息
 *	@note 这个函数会初始化GPS等信息，该函数需要在其它业务函数调用之前调用，返回结果后，再做其它业务函数的请求，内部在定位成功或者失败后都会自己调用 \n
 *		@code - (void)stopLocate @endcode
 *		- 通知的 @ref QLBSServiceMsg .serviceName = @ref QLBSSERVICE_LOCATE
 *		- 通知的 @ref QLBSServiceMsg .result = YES 表示成功
 *		- 通知的 @ref QLBSServiceMsg .result = NO 表示失败 .errocode = 为 kQLBSServiceLocateErr 或者 kQLBSServiceLocateTimeOutErr
 *	@return 是否开始定位
 */
- (BOOL)startLocate;
/**
 *	@brief 取消定位当前的GPS信息
 */
- (void)stopLocate;

/**
 *	@brief 是否开启了定位服务功能，主要用于ios5的判断(设置->定位服务->开关)
 */
- (BOOL)isAbleLocate;

/**
 *	@brief 请求获取当前的位置信息
 *	@note 输出火星坐标与地址，这个方法需要在 @code - (BOOL)startLocate @endcode 成功刷新位置信息后调用，假如从未刷新位置，直接返回FALSE
 *			- 通知的 @ref QLBSServiceMsg .serviceName = @ref QLBSSERVICE_GETCURRPOSITION
 *			- 通知的 @ref QLBSServiceMsg .result = YES 表示成功 .data = @ref QLBSPosition
 *			- 通知的 @ref QLBSServiceMsg .result = NO 表示失败 根据.errocode和.desc获取失败信息描述
 *	@param[in] reqid 请求序列号
 *	@return 请求是否成功
 */
- (BOOL)requestGetCurrentPosition:(int)reqid;
/**
 *	@brief 取消请求获取当前的位置信息
 *	@param[in] reqid 请求序列号
 *	@return 取消请求是否成功
 */
- (void)cancelRequestGetCurrentPosition:(int)reqid;

/**
 *	@brief 请求附近的POI热点信息
 *	@note 这个方法需要在 @code - (BOOL)startLocate @endcode 成功刷新位置信息后调用，假如从未刷新位置，直接放回FALSE
 *			- 通知的 @ref QLBSServiceMsg .serviceName = @ref QLBSSERVICE_GETNEARPOILIST
 *			- 通知的 @ref QLBSServiceMsg .result = YES 表示成功 .data = @ref QLBSPoiInfoBatch
 *			- 通知的 @ref QLBSServiceMsg .result = NO 表示失败 根据.errocode和.desc获取失败信息描述
 *	@param[in] types <NSNumber:NSInteger> 查找POI的类型，为空表示全部类型
 *	@param[in] radius 查找范围半径，单位m，最小精度100m；建议最大不超过1000，否则数据量会太大
 *	@param[in] beginPos 请求记录起始位置，起始为0(翻页使用)
 *	@param[in] reqNum 希望返回一页的POI数量
 *	@param[in] sortMode 希望返回POI的排序方式
 *	@param[in] reqid 请求序列号
 *	@return 请求是否成功
 */
- (BOOL)requestGetNearPoiList:(NSArray*)types radius:(NSUInteger)radius beginPos:(NSUInteger)beginPos reqNum:(NSUInteger)reqNum sortMode:(QLBSPoiSortMode)sortMode requestID:(int)reqid;
/**
 *	@brief 取消请求附近的POI热点信息
 *	@param[in] reqid 请求序列号
 *	@return 取消请求是否成功
 */
- (void)cancelRequestGetNearPoiList:(int)reqid;

/**
 *	@brief 请求关键字搜索附近的POI热点信息
 *	@note 这个方法需要在 @code - (BOOL)startLocate @endcode 成功刷新位置信息后调用，假如从未刷新位置，直接返回FALSE
 *			- 通知的 @ref QLBSServiceMsg .serviceName = @ref QLBSSERVICE_SEARCHNEARPOILIST
 *			- 通知的 @ref QLBSServiceMsg .result = YES 表示成功 .data = @ref QLBSPoiInfoBatch
 *			- 通知的 @ref QLBSServiceMsg .result = NO 表示失败 根据.errocode和.desc获取失败信息描述
 *	@param[in] strKeyword 查找关键字，为空，直接返回FALSE
 *	@param[in] types <NSNumber:NSInteger> 查找POI的类型，为空表示全部类型，该参数只保证输入的类型排在前面，不保证只返回参数里面的类型，因为搜索是个目标模糊的动作，该参数只起提示作用，而不是限制作用
 *	@param[in] radius 查找范围半径，单位m，最小精度100m；建议最大不超过1000，否则数据量会太大
 *	@param[in] beginPos 请求记录起始位置，起始为0(翻页使用)
 *	@param[in] reqNum 希望返回一页的POI数量
 *	@param[in] reqid 请求序列号
 *	@return 请求是否成功
 */
- (BOOL)requestSearchNearPoiList:(NSString*)strKeyword types:(NSArray*)types radius:(NSUInteger)radius beginPos:(NSUInteger)beginPos reqNum:(NSUInteger)reqNum requestID:(int)reqid;
/**
 *	@brief 取消请求关键字搜索附近的POI热点信息
 *	@param[in] reqid 请求序列号
 *	@return 取消请求是否成功
 */
- (void)cancelRequestSearchNearPoiList:(int)reqid;

/**
 *	@brief 判断经纬度是否符合定位平台的定位范围，目前定位平台只是针对国内的Gps有效
 *	@note 假如不符合定位平台的范围，就不用再调用其它定位接口了
 *	@param[in] lat 维度
 *	@param[in] log 经度
 *	@return 是否处于定位平台有效的国内Gps范围
 */
- (BOOL)isPlatformSupport:(double)lat longitude:(double)log;

/**
 *	@brief 获取定位平台api所需要的地理位置信息加密buffer
 *	@note 输出加密buffer，这个方法需要在 @code - (BOOL)startLocate @endcode 成功刷新位置信息后调用，假如从未刷新位置，直接返回nil
 *	@return 加密buffer
 */
- (NSData*)exportPlatformDeviceData;

/**
 *	@brief 获取定位平台api所需要的地理位置信息加密buffer，但是经纬度可以自己控制
 *	@note 输出加密buffer，这个方法同样需要设置用户名和密码，假如从未设置，直接返回nil
 *	@param[in] lat 维度
 *	@param[in] log 经度
 *	@return 加密buffer
 */
- (NSData*)exportPlatformDeviceData:(double)lat longitude:(double)log;

@end


/** @brief 服务结果的载体 */
@interface QLBSServiceMsg : NSObject
/** @brief 服务类型 */
@property (nonatomic, retain) NSString* serviceName;
/** @brief 错误码 */
@property (nonatomic, assign) NSInteger errcode;
/** @brief 请求序列号 */
@property (nonatomic, assign) NSInteger reqID;
/** @brief 结果成功与否 */
@property (nonatomic, assign) BOOL result;
/** @brief 结果数据 */
@property (nonatomic, assign) void* data;
/** @brief 错误描述 */
@property (nonatomic, retain) NSString* desc;
@end

