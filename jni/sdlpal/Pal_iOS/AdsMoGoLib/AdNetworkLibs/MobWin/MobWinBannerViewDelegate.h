//
//  MobWinBannerViewDelegate.h
//  MobWinSDK
//
//  Created by Guo Zhao on 10/28/11.
//  Copyright (c) 2011 Tencent. All rights reserved.
//

@protocol MobWinBannerViewDelegate <NSObject>

@optional


// 请求广告条数据成功后调用
//
// 详解:当接收服务器返回的广告数据成功后调用该函数
- (void)bannerViewDidReceived;

// 请求广告条数据失败后调用
//
// 详解:当接收服务器返回的广告数据失败后调用该函数
- (void)bannerViewFailToReceived;

// 全屏广告弹出时调用
//
// 详解:当广告栏被点击，弹出内嵌全屏广告时调用
- (void)bannerViewDidPresentScreen;

// 全屏广告关闭时调用
//
// 详解:当弹出内嵌全屏广告关闭，返回广告栏界面时调用
- (void)bannerViewDidDismissScreen;

@end
