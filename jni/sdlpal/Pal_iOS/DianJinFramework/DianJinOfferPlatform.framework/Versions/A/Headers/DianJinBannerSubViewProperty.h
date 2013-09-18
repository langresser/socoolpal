//
//  DianJinOfferBannerProperty.h
//  DianJinOfferPlatform
//
//  Created by zhuang zi jiao on 12-2-10.
//  Copyright 2012 NetDragon WebSoft Inc.. All rights reserved.
//

@interface DianJinBannerSubViewProperty : NSObject {
	UIColor *_viewNormalBackgroundColor;
	UIColor *_viewTouchBackgroundColor;
	
	UIColor *_appNameLabelTextNormalColor;
	UIColor *_appNameLabelTextTouchColor;
	
	UIColor *_appDescLabelTextNormalColor;
	UIColor *_appDescLabelTextTouchColor;
	
	UIColor *_appRewardLabelTextColor;
	
	UIColor *_overlayBackgroundColor;
	
	UIColor *_downloadButtonBackgroundColor;
}

@property (nonatomic, retain) UIColor *viewNormalBackgroundColor;		//正常时banner视图背景颜色
@property (nonatomic, retain) UIColor *viewTouchBackgroundColor;		//点击时banner时视图背景颜色

@property (nonatomic, retain) UIColor *appNameLabelTextNormalColor;		//正常时应用名称字体颜色
@property (nonatomic, retain) UIColor *appNameLabelTextTouchColor;		//点击时应用名称字体颜色

@property (nonatomic, retain) UIColor *appDescLabelTextNormalColor;		//正常时应用简介字体颜色
@property (nonatomic, retain) UIColor *appDescLabelTextTouchColor;		//点击时应用简介字体颜色

@property (nonatomic, retain) UIColor *appRewardLabelTextColor;			//奖励描述字体颜色

@property (nonatomic, retain) UIColor *overlayBackgroundColor;			//点击完成时覆盖层背景颜色

@property (nonatomic, retain) UIColor *downloadButtonBackgroundColor;	//下载奖励按钮背景颜色

@end
