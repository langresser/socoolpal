//
//  DMAdView.h
//
//  Copyright (c) 2012 Domob Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>

// For iPhone
#define DOMOB_AD_SIZE_320x50    CGSizeMake(320, 50)
#define DOMOB_AD_SIZE_300x250   CGSizeMake(300, 250)

// For iPad
#define DOMOB_AD_SIZE_448x80    CGSizeMake(488, 80)
#define DOMOB_AD_SIZE_728x90    CGSizeMake(728, 90)
#define DOMOB_AD_SIZE_600x500   CGSizeMake(600, 500)

typedef enum
{
    DMUserGenderFemale,
    DMUserGenderMale
} DMUserGenderType;

@protocol DMAdViewDelegate;
@interface DMAdView : UIView

@property (nonatomic, assign) id<DMAdViewDelegate> delegate;
@property (nonatomic, assign) UIViewController *rootViewController;

// 初始化普通的嵌入式广告视图
- (id)initWithPublisherId:(NSString *)publisherId // Publishier ID
                     size:(CGSize)adSize;         // 广告尺寸

- (id)initWithPublisherId:(NSString *)publisherId // Publishier ID
                     size:(CGSize)adSize          // 广告尺寸
              autorefresh:(BOOL)autorefresh;      // 是否自动刷新

// 加载广告
- (void)loadAd;

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

@protocol DMAdViewDelegate <NSObject>
@optional
// 成功加载广告后，回调该方法
- (void)dmAdViewSuccessToLoadAd:(DMAdView *)adView;
// 加载广告失败后，回调该方法
- (void)dmAdViewFailToLoadAd:(DMAdView *)adView withError:(NSError *)error;

// 当将要呈现出 Modal View 时，回调该方法。如打开内置浏览器。
- (void)dmWillPresentModalViewFromAd:(DMAdView *)adView;
// 当呈现的 Modal View 被关闭后，回调该方法。如内置浏览器被关闭。
- (void)dmDidDismissModalViewFromAd:(DMAdView *)adView;
// 当因用户的操作（如点击下载类广告，需要跳转到Store），需要离开当前应用时，回调该方法
- (void)dmApplicationWillEnterBackgroundFromAd:(DMAdView *)adView;

@end
