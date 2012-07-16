//
//  QLBSLocateManager.h
//  LBSSDK
//
//  Created by easelin on 11-10-14.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

@class QLBSLocationManager;

@protocol QLBSLocationManagerDelegate
/** 
 *	@brief 定位成功回调
 */
- (void)lbsLocationManager:(QLBSLocationManager *)manager locateSuccess:(CLLocation *)location;
/** 
 *	@brief 定位失败回调
 */
- (void)lbsLocationManager:(QLBSLocationManager *)manager locateFailed:(NSError *)error;
/** 
 *	@brief 定位超时回调，带入一个精度最高的
 */
- (void)lbsLocationManager:(QLBSLocationManager *)manager locateTimeOut:(CLLocation *)location;
@end

/**
 *	@brief 定位载体
 */
@interface QLBSLocationManager : NSObject<CLLocationManagerDelegate>
{
	id<QLBSLocationManagerDelegate> _delegate;
	
	CLLocationManager* _sys_manager;
	CLLocation* _last_location;
	NSTimer* _timer;
	
	CLLocationAccuracy _locateAccuracy;
	NSTimeInterval _locateTimeOut;
	BOOL _isUpdatingLocation;
}
/** 
 *	@brief 回调指针
 */
@property (nonatomic, assign) id<QLBSLocationManagerDelegate> delegate;
/** 
 *	@brief 是否在定位过程
 */
@property (nonatomic, readonly) BOOL isUpdatingLocation;
/** 
 *	@brief 定位精度
 *	@note 默认为kCLLocationAccuracyHundredMeters，请勿将该值设置到很高精度，比如kCLLocationAccuracyBest，因为一般情况下面没法到达该精度的要求，会在超时时间过后返回一个精度最高的值
 */
@property (nonatomic, assign) CLLocationAccuracy locateAccuracy;
/** 
 *	@brief 定位超时时间
 *	@note 默认为10s，假如在超时时间内，系统还未找到符合 locateAccuracy 精度的要求，将在该超时时间后返回一个精度最高的值(假如有的话)
 */
@property (nonatomic, assign) NSTimeInterval locateTimeOut;
/** 
 *	@brief 开始定位
 */
- (BOOL)startLocate;
/** 
 *	@brief 取消定位
 */
- (void)stopLocate;
/** 
 *	@brief 是否可以定位(设置->定位服务->开/关)，用于ios5的判断
 */
- (BOOL)isAbleLocate;
@end
