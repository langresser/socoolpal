//
//  DianJinOfferBanner.h
//  DianJinOfferPlatform
//
//  Created by zhuang zi jiao on 12-2-10.
//  Copyright 2012 NetDragon WebSoft Inc.. All rights reserved.
//

typedef enum _DJOfferBannerStyle{
    kDJBannerStyle320_50 = 0,
    kDJBannerStyle480_50
}DJOfferBannerStyle;

@class DianJinBannerView;
@class DianJinTransitionParam;
@class DianJinBannerSubViewProperty;
@class DianJinAppInfoList;
@class DianJinAppInfo;

@interface DianJinOfferBanner : UIView {
	id _delegate;
	DianJinBannerView *_bannerView;
	DJOfferBannerStyle _style;
	DianJinTransitionParam *_transitionParam;
	NSTimer *_bannerRefreshTimer;
	NSTimeInterval _timerInterval;
	BOOL _isAutoRotate;
	BOOL _listRequestRefreshWaitFlag;
	BOOL _touchOperateRefreshWaitFlag;
	int _currentBannerIndex;
	DianJinAppInfo *_currentAppInfo;
	DianJinAppInfoList *_appInfoList;
	DianJinBannerSubViewProperty *_subViewColorProperty;
}

@property (nonatomic, assign) DJOfferBannerStyle style;
@property (nonatomic, assign) BOOL isAutoRotate;

- (id)initWithOfferBanner:(CGPoint)origin style:(DJOfferBannerStyle)style;
- (void)startWithTimeInterval:(NSTimeInterval)ti delegate:(id)delegate;
- (int)setupTransition:(DianJinTransitionParam *)param;
- (void)setupSubViewProperty:(DianJinBannerSubViewProperty *)property;
- (void)stop;

@end

@protocol DianJinOfferBannerDelegate<NSObject>

- (void)appActivatedDidFinish:(NSDictionary *)resultDic;

@end

