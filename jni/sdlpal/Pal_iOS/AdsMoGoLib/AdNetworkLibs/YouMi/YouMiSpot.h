//
//  YouMiSpot.h
//  YouMiSDK
//
//  Created by Layne on 10-11-30.
//  Copyright 2010 YouMi Mobile Co. Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import "YouMiSpotDelegateProtocol.h"


// Spot request for the display types from server
// 
// 插播向服务器请求需要展示的类型
typedef enum {
	YouMiSpotDisplayFormForRequestUnknow					= 0,	// unknown
	YouMiSpotDisplayFormForRequestLandscape                 = 1,	// Landscape
	YouMiSpotDisplayFormForRequestPortrait					= 2,	// Portrait
	YouMiSpotDisplayFormForRequestLandscapeAndPortrait		= 3,	// Lanscape+Portrait
} YouMiSpotDisplayFormForRequest;

// Presenting the display form of spot
//
// 显示插播广告的展示形式
typedef enum {
	YouMiSpotDisplayFormPortrait			= 1,
	YouMiSpotDisplayFormPortraitUpsideDown	= 2,
	YouMiSpotDisplayFormLandscapeRight		= 3,
	YouMiSpotDisplayFormLandscapeLeft		= 4
} YouMiSpotDisplayForm;

// Models of spot ad progress
//
// 插播广告进度条样式
typedef enum {
	YouMiSpotProgressType1 = 1,
	YouMiSpotProgressType2 = 2,
	YouMiSpotProgressType3 = 3
} YouMiSpotProgressType;

// Animation types of spot ad
//
// 插播广告展示的动画类型
typedef enum {
	YouMiSpotPresentType1	= 1,
	YouMiSpotPresentType2	= 2,
	YouMiSpotPresentType3	= 3,
	YouMiSpotPresentType4	= 4,
	YouMiSpotPresentType5	= 5
} YouMiSpotPresentType;


@protocol YouMiSpotDelegate;


@interface YouMiSpot : NSObject

// [AppID] Developer application ID
// visit YouMi website: http://www.youmi.net/, register a developer account 
// and sign in with an application, to get the corresponding ID for your application

// 开发者应用ID
// 
// 详解:
//      前往有米主页:http://www.youmi.net/ 注册一个开发者帐户，
//      同时注册一个应用，获取对应应用的ID
// 
@property(nonatomic, copy)                      NSString    *appID;

// [AppSecret] Developer security key
// visit YouMi website: http://www.youmi.net/, register a developer account 
// and sign in with an application, to get the cooresponding security key
//
// 开发者的安全密钥
//
// 详解:
//      前往有米主页:http://www.youmi.net/ 注册一个开发者帐户，
//      同时注册一个应用，获取对应应用的安全密钥
// 
@property(nonatomic, copy)                      NSString    *appSecret;

// Information about the version of the application
// @return the version information of the application
// p.s. the returned version number shall adopt the float like 1.0 or 1.2. 
// at present the server doesn's support version forms like 1.1.1, 
// but forms like 1.12 are accepted
// 
// 应用的版本信息
// 
// Default:
//      @"Bundle version"
// 详解:
//      返回开发者自己应用的版本信息
// 补充:
//      返回的版本号需要使用浮点的类型,比如版本为1.0或者1.2等，目前服务器不支持1.1.1等版本的形式，有效低位版本只有一位，可以为1.12等
// 
@property(nonatomic, copy)                      NSString    *appVersion;

// Channel ID 
// channel ID is used for application promotion
// p.s. channel ID can be 1 -> 255
//
// 应用发布的渠道号
// Default:
//      @1
// 详解:
//      该参数主要给先推广该应用的时候，打包的渠道号
// 补充:
//      可以渠道号 1 -> 255
// 
@property(nonatomic, assign)                    NSInteger   channelID;

// Request mode of spot ad
// @No: normal 
// @YES: test
// normal request, recording display and click results
// test request under test mode, without recording display and click results
// p.s. By default, Simulator is under testing and the real device is under normal mode; 
// and developer can't set the normal mode on Stimulator.
//
// 插播广告请求模式
//      模拟器@YES 真机器@NO
// 详解:
//      广告请求的模式 [NO:正常模式 YES:测试模式] 
//      正常模式:按正常广告请求，记录展示和点击结果
//      测试模式:开始测试情况下请求，不记录展示和点击结果
// 备注:
//      默认是模拟器是测试模式,真机是正常模式，若开发者在模拟器上面使用的时候，无法设置为正常模式
//
@property(nonatomic, assign, getter=isTesting)  BOOL        testing;

// Delegate
// 
// 委托
// 
@property(nonatomic, assign)id<YouMiSpotDelegate> delegate;

// Request the upcoming present mode of spot ad
// 1.landscape  2. portrait  3.landscape+portrait
// for example
// 1. landscape --> requested spot ad size 480x320
// 2. portrait --> requested spot ad size 320x480
// 3. landscape+portrait --> requested spot ad size is 320x480 or 480x320
// if the application only supports landscape, return to 1. If it only supports portrait, return to 2. If it supports both, return to 3.
// 
// 请求插播广告的将要展示的形式
// 详解:
//      1:横屏 2:竖屏 3:横屏或者竖屏
//      比如iPhone
//      1.横屏 --> 请求的插播广告大小尺寸是480x320，用于横屏显示
//      2.竖屏 --> 请求的插播广告大小尺寸是320x480，用于竖屏显示
//      3.横屏或者竖屏 --> 请求的插播广告大小尺寸是320x480 和 480x320，可以用于竖屏显示，也可以用于横屏显示
//      若应用只支持横屏模式，则返回1。若只支持竖屏模式，则返回2。若应用支持横屏和竖屏，则返回3
// 备注:
//      该属性区别于YouMiSpot里面的显示插播广告的方法
//      - (BOOL)showAdSpotWithDisplayForm:(YouMiSpotDisplayForm)displayForm
//                           progressType:(YouMiSpotProgressType)progressType
//                            presentType:(YouMiSpotPresentType)presentType
//                            promptTitle:(NSString *)title
//      该方法里面的YouMiSpotDisplayForm是显示插播广告的具体展示模式
//      而displayFormForSpotAd里面的返回的展示形式是要请求服务器的插播广告类型
//      若请求返回1[横屏]，则后面获取到的插播广告只能用YouMiSpotDisplayFormLandscapeRight或者YouMiSpotDisplayFormLandscapeLeft来显示
//      若请求返回2[竖屏]，则后面获取到的插播广告只能用YouMiSpotDisplayFormPortrait或者YouMiSpotDisplayFormPortraitUpsideDown来显示
//      若请求返回3[横屏或者竖屏]，则获取的插播广告内容是有横屏模式，也有竖屏模式，所以四种显示模式都可以显示
// 
@property(nonatomic, assign) YouMiSpotDisplayFormForRequest displayFormForRequest;

// The minimal time allowed to request spot ad
// @3.0
// by default, the minimal time allowed to request spot ad from server is 3 seconds
//
// 请求插播广告允许的最小时间
// Default:
//      @3.0
// 详解:
//      返回允许请求服务器目前可用插播广告的时间长度的最小值，默认是3秒
//
@property(nonatomic, assign) NSUInteger minAllowedTime;

// The maximal time allowed to request spot ad
// @10.0
// by default, the maximal time allowed to request spot ad from server is 10 seconds
//
// 请求插播广告允许的最大时间
// Default:
//      @10.0
// 详解:
//      返回允许请求服务器目前可用插播广告的时间长度的最大值，默认是10秒
//
@property(nonatomic, assign) NSUInteger maxAllowedTime;


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

// Whether to allowing using sqlite3 to save pics downloaded from the Internet, 
// in order to save flow
// @YES
// 
// 是否允许使用sqlite3来替用户保存一些下载的图片，以便节省用户的流量
// Default:
//      @YES
// 详解:
//      帮助用户节省流量，同时加快广告显示速度
// 
+ (void)setShouldCacheImage:(BOOL)flag;

// Single instance of YouMiSpot
// 
// YouMiSpot的单实例
// 详解:
//      返回一个YouMiSpot的单实例
// 
+ (YouMiSpot *)sharedAdSpot;

// Start to request spot ad
// start to request spot ad. After set, please rememer to send this WinMain, 
// to inform backend of starting request spot ad from server
// 
// 开始请求插播广告
// 详解:
//      入口方法，开始请求插播广告，当你设置完成后，务必记得调用该方法，以便通知后台开始请求服务器插播广告
// 
-(void)startAdSpotRequest;

// Whether the spot ad is ready for show
// please confirm the spot ad is ready before showAdspot sent
// @YES -> ready to present spot ad
// @No -> spot ad is not ready yet, and it might be unable to display if send showSdSpot
//
// 插播广告是否已经准备完毕
// 详解:
//      每次调用showAdSpot之前请务必确认插播广告已经准备就绪
// 返回值:
//      YES->可以显示插播广告  
//      NO->插播广告当前还没有准备就绪，若调用showAdSpot则有可能无法正常显示
// 
- (BOOL)isReadyForShow;

// Display spot ad if it has been successfully fetched from the server
// please be sure of starting to request ad before send
// displayForm  : display mode of spot ad
// progressType : types of floating progress bar whiling present spot ad
// presentType  : animation type while presenting spot ad [match between appearance and disappearance]
// title        : notification on progress bar while presenting spot ad
//
// 显示插播广告，若广告已经成功从服务器获取下来
// 详解:
//      调用该方法前，请务必确保之前已经开始请求广告
//      返回当前是否显示成功
//      参数->displayForm         : 显示插播广告的模式
//      参数->progressType        : 显示插播广告，表面浮动的进度条的类型
//      参数->presentType         : 显示插播广告，出现的动画类型[消失动画类型和出现动画类型匹配]
//      参数->title               : 显示插播广告，进度条上面的提示语言
// 
- (BOOL)showAdSpotWithDisplayForm:(YouMiSpotDisplayForm)displayForm
					 progressType:(YouMiSpotProgressType)progressType
					  presentType:(YouMiSpotPresentType)presentType
					  promptTitle:(NSString *)title;

@end
