//
//  DianJinAdBanner.h
//  DianJinOfferDemo
//
//  Created by xie huaiqing on 13-3-26.
//
//

typedef enum {
    kDJCPCBannerStyle320_50 = 0,
    kDJCPCBannerStyle728_90
}DJCPCBannerStyle;

@class DianJinTransitionParam;

@protocol DianJinAdBannerDelegate;

@interface DianJinAdBanner : UIView

@property (nonatomic, assign) id<DianJinAdBannerDelegate> delegate;

//初始化Banner广告
- (id)initAdBannerWithOrigin:(CGPoint)origin size:(DJCPCBannerStyle)size;
//设置方向
- (void)setBrowserOrientation:(UIInterfaceOrientation)orientation;
//设置自动旋转
- (void)setBrowserAutoRotate:(BOOL)isAutoRotate;
//设置广告动画
- (void)setupTransitionParam:(DianJinTransitionParam *)param;
//设置导航栏颜色
- (void)setBrowserNavigationBarColor:(UIColor *)navigationBarColor;

@end

@protocol DianJinAdBannerDelegate <NSObject>

@optional
- (void)adLoadSuccess;
- (void)adLoadFail;
- (void)adBrowserDidShow;
- (void)adBrowserDidHide;

@end
