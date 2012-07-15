/*

 AdViewView.h

 Copyright 2010 www.adview.cn. All rights reserved.

*/

#import <UIKit/UIKit.h>
#import "AdViewDelegateProtocol.h"

#define KADVIEW_APP_VERSION		101

#define KADVIEW_WIDTH	320
#define KADVIEW_HEIGHT	50

#define KADVIEW_ZERO_SIZE (CGSizeMake(0, 0))

#define KADVIEW_DETAULT_SIZE (CGSizeMake(KADVIEW_WIDTH, KADVIEW_HEIGHT))

#define KADVIEW_DETAULT_FRAME (CGRectMake(0,0,KADVIEW_WIDTH, KADVIEW_HEIGHT))

#define KLANDSCAPE_WIDTH	480
#define KLANDSCAPE_HEIGHT	32

#define KLANDSCAPE_DETAULT_FRAME (CGRectMake(0,0,KLANDSCAPE_WIDTH, KLANDSCAPE_HEIGHT))

#define KADVIEW_PUBLISH_CHANNEL_APPSTORE @"AppStore"
#define KADVIEW_PUBLISH_CHANNEL_CYDIA @"Cydia"
#define KADVIEW_PUBLISH_CHANNEL_91Store @"91Store"

@interface AdViewView : UIView {
	id<AdViewDelegate> delegate;
	
	NSError *lastError;	
	
	NSArray *testDarts;
	NSUInteger testDartIndex;	
}

/**
 * 托管对象，注意如果要释放adView，先将这个值设为nil。
 * 如果要切换托管对象，请确保切换后的对象有效，比如正确返回adView id，及使用的广告id
 */
@property (nonatomic, assign) IBOutlet id<AdViewDelegate> delegate;

/**
 * 错误信息对象
 */
@property (nonatomic, readonly) NSError *lastError;
@property (nonatomic,retain) NSArray *testDarts;

/**
 * 创建adView视图
 */
+ (AdViewView *)requestAdViewViewWithDelegate:(id<AdViewDelegate>)delegate;

/**
 * 从服务器重新下载config配置。
 */
- (void)updateAdViewConfig;

/**
 * 更新同一平台的广告，因为有自动更新功能，不推荐调用。
 */
- (void)requestFreshAd;

/**
 * 手动切换到下个平台广告，因为有自动更新功能，因此并不推荐调用。
 */
- (void)rollOver;

/**
 * 不同的广告有不同的大小，请在delegate的adViewDidReceiveAd回调中获取这个数值以使用。
 */
- (CGSize)actualAdSize;

/**
 * 有些广告在旋转屏幕时有特殊要求，可能需要调用此接口以保证正常。
 */
- (void)rotateToOrientation:(UIInterfaceOrientation)orientation;

/**
 * 获得最近使用广告名称
 */
- (NSString *)mostRecentNetworkName;

/**
 * 用参数视图替换adView视图
 */
- (void)replaceBannerViewWith:(UIView*)bannerView;

/**
 * 是否开始或者停止AdView的自动刷新广告功能，有些Ad的sdk带自动刷新功能，因此虽然AdView停止自动刷新，广告可能仍然自动刷新
 */
- (void)stopAutoRefresh;
- (void)startAutoRefresh;
- (BOOL)isAutoRefreshStarted;

@end
