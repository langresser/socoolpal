//
//  DianJinTransitionParameters.h
//  DianJinOfferPlatform
//
//  Created by zhuang zi jiao on 12-2-10.
//  Copyright 2012 NetDragon WebSoft Inc.. All rights reserved.
//

typedef enum _DJBannerAnimationType {
	kDJTransitionRippleEffect,		//滴水效果
	kDJTransitionCube,				//立方体效果
	kDJTransitionOglFlip,			//翻转效果
	kDJTransitionPageCurl,			//向上翻一页
	kDJTransitionPageUnCurl,		//向下翻一页
	kDJTransitionMoveIn,			//移入效果
	kDJTransitionReveal,			//普通显示效果
	kDJTransitionFade				//淡出效果
}DJBannerAnimationType;

typedef enum _DJBannerAnimationSubType {
	kDJTransitionFromRight,
	kDJTransitionFromLeft,
	kDJTransitionFromTop,
	kDJTransitionFromBottom
}DJBannerAnimationSubType;

@interface DianJinTransitionParam : NSObject {
	DJBannerAnimationType _animationType;
	DJBannerAnimationSubType _animationSubType;
	CFTimeInterval _duration;
}

@property (nonatomic, assign) DJBannerAnimationType animationType;
@property (nonatomic, assign) DJBannerAnimationSubType animationSubType;
@property (nonatomic, assign) CFTimeInterval duration;

+ (DianJinTransitionParam *)getTransitionParam:(DJBannerAnimationType)type subtype:(DJBannerAnimationSubType)subtype transitionDuration:(CFTimeInterval)transitionDuration;

@end
