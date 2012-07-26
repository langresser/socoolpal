//
//  GAdsSDK.h
//  GAds-SDK
//
//  Created by guowei huang on 12-2-13.
//  Copyright (c) 2012年 renren. All rights reserved.
//
#import <Foundation/Foundation.h>

typedef enum 
{
    MODEL_TEST,    //测试模式
    MODEL_RELEASE  //发布模式
} Model;


@interface AderSDK : NSObject

//启动广告服务程序，启动后将轮询调度广告展示，此服务只启动一次
+ (void)startAdService:(UIView *)_parentView appID:(NSString *)appID adFrame:(CGRect)frame model:(Model)model;

//暂停或继续广告服务程序(pause为YES执行暂停，pause为NO执行继续)
+ (void)pauseAdService:(BOOL)pause;

//停止广告服务程序、移除广告、释放内存，需重新启动广告服务程序才能显示广告
+ (void)stopAdService;

//设置委托，接收SDK反馈
+ (void)setDelegate:(id)delegate;

//重新设置AdsView坐标
+ (void)setAdsViewPoint:(CGPoint)point;
@end
