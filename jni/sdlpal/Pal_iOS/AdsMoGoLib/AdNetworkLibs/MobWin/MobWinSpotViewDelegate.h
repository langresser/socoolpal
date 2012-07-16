//
//  MobWinSpotViewDelegate.h
//  MobWinSDK
//
//  Created by Guo Zhao on 11-12-7.
//  Copyright 2011 Tencent. All rights reserved.
//
//

#import <Foundation/Foundation.h>

// 插播广告状态接收代理方法
@protocol MobWinSpotViewDelegate <NSObject>

@optional

// 插播广告获取成功
// 
// 详解:请求插播广告成功时调用
- (void)spotViewDidReceived;

// 插播广告获取失败
// 
// 详解:请求插播广告失败时调用
- (void)spotViewDidReceivedFailed;

// 将要展示插播广告前调用
// 
// 详解:将要展示一次插播广告内容前调用
- (void)spotViewWillPresentScreen;

// 成功展示插播广告后调用
// 
// 详解:插播广告展示开始时调用
- (void)spotViewDidPresentScreen;

// 将要结束插播广告前调用
//
// 详解:插播广告展示完成，将要结束插播广告前调用
- (void)spotViewWillDismissScreen;

// 成功结束插播广告后调用
//
// 详解:插播广告展示完成，结束插播广告后调用
- (void)spotViewDidDismissScreen;


@end