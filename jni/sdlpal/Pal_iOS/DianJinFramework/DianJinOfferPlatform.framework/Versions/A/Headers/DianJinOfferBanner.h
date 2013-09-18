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

@class DianJinTransitionParam;
@class DianJinBannerSubViewProperty;

@interface DianJinOfferBanner : UIView {
	DJOfferBannerStyle _style;
	BOOL _isAutoRotate;
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

