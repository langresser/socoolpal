//
//  YouMiView.h
//  YouMiSDK
//
//  Created by Layne on 10-8-31.
//  Copyright 2010 YouMi Mobile Co. Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import "YouMiDelegateProtocol.h"


typedef enum {
    YouMiBannerContentSizeIdentifierUnknow     = 0,
    YouMiBannerContentSizeIdentifier320x50     = 1, // iPhone and iPod Touch ad size
    YouMiBannerContentSizeIdentifier200x200    = 2, // Minimum Rectangle size for the iPad
    YouMiBannerContentSizeIdentifier300x250    = 3, // Medium Rectangle size for the iPad (especially in a UISplitView's left pane
    YouMiBannerContentSizeIdentifier468x60     = 4, // Full Banner size for the iPad (especially in a UIPopoverController or in UIModalPresentationFormSheet)
    YouMiBannerContentSizeIdentifier728x90     = 5, // Leaderboard size for the iPad
} YouMiBannerContentSizeIdentifier;


@protocol YouMiDelegate;


@interface YouMiView : UIView

// AppID
// visit YouMi website: http://www.youmi.net/, register a develope account 
// and sign with an application, to get a corresponding ID
//
// 开发者应用ID
// 
// 详解:
//      前往有米主页:http://www.youmi.net/ 注册一个开发者帐户，同时注册一个应用，获取对应应用的ID
// 
@property(nonatomic, copy)                      NSString    *appID;

// AppSecret
// visit YouMi website: http://www.youmi.net/, register a developer account and sign with an application, to get a corresponding ID
// 
// 开发者的安全密钥
// 
// 详解:
//      前往有米主页:http://www.youmi.net/ 注册一个开发者帐户，同时注册一个应用，获取对应应用的安全密钥
// 
@property(nonatomic, copy)                      NSString    *appSecret;

// App Version  
// @"Bundle version"
// p.s. the returned version number shall adopt the float like 1.0 or 1.2. 
// at present the server doesn's support version forms like 1.1.1, but forms like 1.12 are accepted
//
// 应用的版本信息
// Default:
//      @"Bundle version"
// 详解:
//      返回开发者自己应用的版本信息
// 补充:
//      返回的版本号需要使用浮点的类型,比如版本为1.0或者1.2等，目前服务器不支持1.1.1等版本的形式，有效低位版本只有一位，可以为1.12等
//
@property(nonatomic, copy)                      NSString    *appVersion;


// Channel ID 
// @1
// channel ID is used for application promotion
// p.s. channel ID can be 1 -> 255
// 
// 应用发布的渠道号
// Defatut:
//      @1
// 详解:
//      该参数主要给先推广该应用的时候，打包的渠道号
// 补充:
//      可以渠道号 1 -> 255
// 
@property(nonatomic, assign)                    NSInteger   channelID;

// request mode of banner ad
// ads request mode [No: normal  YES: test]
// normal: normal request, recording display and click results
// test: request under test mode, without recording display and click results
// p.s. By default, Simulator is under testing and the real device is under normal mode; 
// and developer can't set the normal mode on Stimulator
// 
// 广告条请求模式
// 模拟器@YES 真机器@NO
// 详解:
//      广告请求的模式 [NO:正常模式 YES:测试模式] 
//      正常模式:按正常广告请求，记录展示和点击结果
//      测试模式:开始测试情况下请求，不记录展示和点击结果
// 备注:
//      默认是模拟器是测试模式,真机是正常模式，若开发者在模拟器上面使用的时候，无法设置为正常模式
// 
@property(nonatomic, assign, getter=isTesting)  BOOL        testing;

// The size of banner
// @YouMiBannerContentSizeIdentifierUnknow
//
// YouMiBannerContentSizeIdentifierUnknow   --> unknown
// YouMiBannerContentSizeIdentifier320x50   --> CGSizeMake(320, 50)
// YouMiBannerContentSizeIdentifier200x200  --> CGSizeMake(200, 200)
// YouMiBannerContentSizeIdentifier300x250  --> CGSizeMake(300, 250)
// YouMiBannerContentSizeIdentifier468x60   --> CGSizeMake(468, 60)
// YouMiBannerContentSizeIdentifier728x90   --> CGSizeMake(728, 90)
// 
// 广告条的尺寸 
//
@property(nonatomic, assign, readonly)          YouMiBannerContentSizeIdentifier contentSizeIdentifier;

// Delegate
//
// 委托
//
@property(nonatomic, assign)                                id<YouMiDelegate> delegate;

// Indicate banner border
// @YES
// YES->banner with white frame
// No->Banner without white frame
//
// 广告条边框
// Default:
//      @YES
// 详解:
//      YES->广告条将会显示白色边框
//      NO->广告条去掉默认白色边框
//
@property(nonatomic, assign, getter=isIndicateBorder)       BOOL indicateBorder;

// Indicate banner trasparency
// @YES
// YES->banner with trasparency effect
// No->banner without transparency effect
// 
// 广告条透明效果
// Default:
//      @YES
// 详解:
//      YES->广告条显示透明效果
//      NO->广告条取消默认透明效果
//
@property(nonatomic, assign, getter=isIndicateTranslucency) BOOL indicateTranslucency;

// Indicate banner round corner
// @YES
// YES-> banner with round corner effect
// NO->banner without round corner effect
//
// 广告条圆角
// Default:
//      @YES
// 详解:
//      YES->广告条显示圆角效果
//      NO->广告条无圆角
// 
@property(nonatomic, assign, getter=isIndicateRounded)      BOOL indicateRounded;

// Background color of text banner ad
// @{64/255.0, 118/255.0, 170/255.0, 1.0}
// 
// 背景颜色
// 详解:
//      主要是文字广告的时候，广告条的背景颜色
// 
@property(nonatomic, retain) UIColor *indicateBackgroundColor;

// Title color of text banner ad
// @{255/255.0, 255/255.0, 255/255.0, 1.0}
//
// 主标题颜色
// 详解:
//      主要是文字广告的时候，主标题的颜色
// 
@property(nonatomic, retain) UIColor *textColor;

// Sub-title color of text banner ad
// @{255/255.0, 255/255.0, 255/255.0, 1.0}
//
// 副标题颜色
// 详解:
//      主要是文字广告的时候，副标题的颜色
// 
@property(nonatomic, retain) UIColor *subTextColor;


// SDK Version
// 
+ (NSString *)sdkVersion;


// Set should get the location of the user
// @YES
// When YES the app will use GPS to get the location of the user
// and support accurate targeting of advertising
// 
// 统计定位请求
// Default:
//      @YES
// 详解:
//      返回是否允许使用GPS定位用户所在的坐标，主要是为了帮助开发者了解自己应用的分布情况，同时帮助精准投放广告需要
//      [默认定位以帮助开发者了解自己软件精确投放广告]
// 
+ (void)setShouldGetLocation:(BOOL)flag;

// Whether to allowing using sqlite3 to save pics downloaded from the Internet, in order to save traffic
// help user to save traffic, and raise the ad display speed at the same time
// 
// 是否允许使用sqlite3来替用户保存一些下载的图片，以便节省用户的流量
// Default:
//      @YES
// 详解:
//      帮助用户节省流量，同时加快广告显示速度
// 
+ (void)setShouldCacheImage:(BOOL)flag;


+ (YouMiView *)adViewWithContentSizeIdentifier:(YouMiBannerContentSizeIdentifier)contentSizeIdentifier delegate:(id<YouMiDelegate>)delegate;
- (id)initWithContentSizeIdentifier:(YouMiBannerContentSizeIdentifier)contentSizeIdentifier delegate:(id<YouMiDelegate>)delegate;

// Start to request banner ad
// 
// 开始请求广告
// 
// 详解:
//      若想停用定位请求，或者图片缓存，
//      则在开始广告请求前请先调用+ (void)setShouldGetLocation:(BOOL)flag 和 + (void)setShouldCacheImage:(BOOL)flag
//
- (void)start;

// Key words
// to match with ad data, encourge users to review ads
// 
// 添加关键字
// 
// 详解:
//      主要是用于精准匹配广告数据，增强用户点击广告的概念
// 
- (void)addKeyword:(NSString *)keyword;

@end
