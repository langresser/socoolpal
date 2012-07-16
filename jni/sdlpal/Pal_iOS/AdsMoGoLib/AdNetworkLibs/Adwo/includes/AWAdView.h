//
//  AWAdView.h
//  Copyright 2011 Adwo.com All rights reserved.
//
#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <MessageUI/MessageUI.h>
#import <MediaPlayer/MPMoviePlayerViewController.h>
#import <MediaPlayer/MPMoviePlayerController.h>
#import <CoreLocation/CoreLocation.h>


@protocol AWAdViewDelegate;
@protocol AWAdBrowserControllerDelegate;
@protocol AWMailViewControllerDelegate;
@protocol AWMapViewControllerDelegate; 

@class AWTimer;
@class AWAdDevice;
@interface UIDevice (Hardware)
+ (NSString *) getSysInfoByName:(char *)typeSpecifier;
+ (NSString *) platform;
@end


enum ADWO_ADS_BANNER_SIZE_FOR_IPAD
{
    ADWO_ADS_BANNER_SIZE_FOR_IPAD_320x50 = 1 << 0,
    ADWO_ADS_BANNER_SIZE_FOR_IPAD_640x100 = 1 << 1,
    ADWO_ADS_BANNER_SIZE_FOR_IPAD_720x110 = 1 << 2
};


@interface AWAdView : UIView <UIWebViewDelegate,AWAdBrowserControllerDelegate,UIAlertViewDelegate,AWMailViewControllerDelegate,AWMapViewControllerDelegate> 

{
    
    id <AWAdViewDelegate> _delegate;
    
    BOOL _isLoading;
    NSURLConnection *_conn;
    NSURLConnection *_connDownloadPic;
    NSURLConnection * _connBeconUrl;
    NSURLConnection *_connNewUrl;
    
	AWTimer *_autorefreshTimer;
    NSMutableData *_data;
    NSMutableData *_dataPic;
    NSMutableData *_fixData; 
    NSMutableData *_dataUrl;
    UIView *_adContentView;
    UIView *_adTempView;
    int _animationType;
    BOOL _adActionInProgress;
    BOOL _autorefreshTimerNeedsScheduling;
    BOOL _ignoresAutorefresh;
    CGSize _originalSize;
    CGSize creativeSize;
    NSMutableArray *_clickedAds; 
    
    NSString *_adUnitId;         // 系统ID,  由开发者在adwo.com 注册获得, 16个字符，32字节
    SInt8 _adIdType;             
    SInt8 _adPayType;            // 计费方式  1：计费 或者 0：测试
    SInt8 _adSizeForPad;
    
    int _adType;            
    
    int _adId;                   
    unsigned short _lastDataLen; 
    NSString * _clickURL;        
    NSString *_realClickURL;     
    int _clickType;     
    SInt8 _adTextLen;            
    NSString *_adTextContent;    
    NSURL *_adPicDownLoadURL;       
    NSURL *_adFSPicDwonLoadURL;        
    short _beaconflag;           
    NSURL *_beaconURL;           
    UIColor * _fontColor;          // 字体颜色
    
    int _deviceType;    //设备名字
    SInt8 _sysVertion;  
    CLLocationManager *_locManager;
    
    float _adRequestTimeIntervel; //广告请求间隔时间 
    int ant[3];     // 增加的3个接收字段（v2.4）
    NSMutableArray*  _showBeacons; 
    NSMutableArray*  _clickBeacons;  
    NSMutableArray*  _controlBeacons;
    BOOL isToCancelAll;
    BOOL isSameAdClicked;
    CGSize _websize;
    CGSize _viewSize;
    UIButton *button1;
    NSString *_reUrl;
    AWAdDevice *adDevice;
    UIWebView *_webview;
}

@property (nonatomic,assign) id <AWAdViewDelegate> delegate;
@property (nonatomic,assign) SInt8 adSizeForPad;

@property (nonatomic,assign) float adRequestTimeIntervel;//广告请求间隔时间//
@property (nonatomic,assign) bool userGpsEnabled; // 是否允许SDK获得用户位置信息

- (id)initWithAdwoPid:(NSString *)unid adIdType:(SInt8) adIdType adTestMode:(SInt8) adTestMode adSizeForPad:(SInt8)adSizeForPad;
- (void)loadAd;
- (void)pauseAd;
- (void)resumeAd;

- (void)killTimer;

@end


@protocol AWAdViewDelegate <NSObject>

@required

- (UIViewController *)viewControllerForPresentingModalView;

@optional

- (void)adViewDidFailToLoadAd:(AWAdView *)view;
- (void)adViewDidLoadAd:(AWAdView *)view;
- (void)willPresentModalViewForAd:(AWAdView *)view;
- (void)didDismissModalViewForAd:(AWAdView *)view;

@end