//
//  DMInterstitialAdViewController.h
//
//  Copyright (c) 2012 Domob Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DMAdView.h"

@protocol DMInterstitialAdControllerDelegate;
@interface DMInterstitialAdController : UIViewController

@property (nonatomic, assign) NSObject<DMInterstitialAdControllerDelegate> *delegate; 
@property (nonatomic, readonly) BOOL isReady;

// 初始化一个插屏广告控制器，默认尺寸为全屏
- (id)initWithPublisherId:(NSString *)publisherId
       rootViewController:(UIViewController *)rootViewController;

// 初始化一个插屏广告控制器，使用开发者指定的尺寸
- (id)initWithPublisherId:(NSString *)publisherId
       rootViewController:(UIViewController *)rootViewController
                     size:(CGSize)adSize;

// 加载广告
- (void)loadAd;

// 呈现广告
- (void)present;

// 设置地理位置信息
- (void)setLocation:(CLLocation *)location;

// 设置邮编
- (void)setPostcode:(NSString *)postcode;

// 设置关键字
- (void)setKeywords:(NSString *)keywords;

// 设置用户年龄
- (void)setUserBirthday:(NSString *)userBirthday;

// 设置用户性别
- (void)setUserGender:(DMUserGenderType)userGender;
@end

////////////////////////////////////////////////////////////////////////////////////////////////////

@protocol DMInterstitialAdControllerDelegate <DMAdViewDelegate>
@optional
// 当插屏广告被成功加载后，回调该方法
- (void)dmInterstitialSuccessToLoadAd:(DMInterstitialAdController *)dmInterstitial;
// 当插屏广告加载失败后，回调该方法
- (void)dmInterstitialFailToLoadAd:(DMInterstitialAdController *)dmInterstitial withError:(NSError *)err;

// 当插屏广告要被呈现出来前，回调该方法
- (void)dmInterstitialWillPresentScreen:(DMInterstitialAdController *)dmInterstitial;
// 当插屏广告被关闭后，回调该方法
- (void)dmInterstitialDidDismissScreen:(DMInterstitialAdController *)dmInterstitial;

// 当将要呈现出 Modal View 时，回调该方法。如打开内置浏览器。
- (void)dmInterstitialWillPresentModalView:(DMInterstitialAdController *)dmInterstitial;
// 当呈现的 Modal View 被关闭后，回调该方法。如内置浏览器被关闭。
- (void)dmInterstitialDidDismissModalView:(DMInterstitialAdController *)dmInterstitial;
// 当因用户的操作（如点击下载类广告，需要跳转到Store），需要离开当前应用时，回调该方法
- (void)dmInterstitialApplicationWillEnterBackground:(DMInterstitialAdController *)dmInterstitial;
@end
