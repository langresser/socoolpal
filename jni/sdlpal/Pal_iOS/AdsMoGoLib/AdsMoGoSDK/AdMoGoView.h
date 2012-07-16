//
//  File: AdMoGoView.h
//  Project: AdsMOGO iOS SDK
//  Version: 1.1.9
//
//  Copyright 2011 AdsMogo.com. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AdMoGoDelegateProtocol.h"
#import "AMNetworkReachabilityWrapper.h"
#import "AdMoGoConfig.h"
#import <CoreLocation/CoreLocation.h>
#import <MapKit/MapKit.h>
#import "AdMoGoAdNetworkAdapter.h"

typedef enum {
    AdViewTypeUnknown = 0,          //error
	AdViewTypeNormalBanner = 1,     //e.g. 320 * 50 ; 320 * 48...  iphone banner
    AdViewTypeLargeBanner = 2,      //e.g. 728 * 90 ; 768 * 110    ipad only
    AdViewTypeMediumBanner = 3,     //e.g. 468 * 60 ; 508 * 80     ipad only
    AdViewTypeRectangle = 4,        //e.g. 300 * 250; 320 * 270    ipad only 
    AdViewTypeSky = 5,              //Don't support
    AdViewTypeFullScreen = 6,       //iphone full screen ad
    AdViewTypeVideo = 7,            //Don't support
    AdViewTypeiPadNormalBanner = 8, //ipad use iphone banner
} AdViewType;

@class AdMoGoAdNetworkConfig;
@class AdMoGoAdNetworkAdapter;
@class AdMoGoConfigStore;
@class AMNetworkReachabilityWrapper;

@interface AdMoGoView : UIView <AdMoGoConfigDelegate,
AMNetworkReachabilityDelegate,
CLLocationManagerDelegate,
MKReverseGeocoderDelegate,UIAlertViewDelegate> {
	id<AdMoGoDelegate> delegate;
	AdMoGoConfig *config;
    AdMoGoConfig *onlineConfig;
    AdMoGoAdNetworkConfig *adfConfig;
    
	NSMutableArray *prioritizedAdNetCfgs;
    NSMutableArray *bfprioritizedAdNetCfgs;
	double totalPercent;
    double bfTotalPercent;
    NSMutableString *lastShowAdNetworkNid;
    NSUInteger lastShowAdNetworkType;
    NSInteger isBf;
	
	BOOL appInactive;
	BOOL showingModalView;
    BOOL pauseAdRequest;
	BOOL requesting;
    
	AdMoGoAdNetworkAdapter *currAdapter;
	AdMoGoAdNetworkAdapter *lastAdapter;
    AdMoGoAdNetworkAdapter *tempAdapter;
	NSDate *lastRequestTime;
	NSMutableDictionary *pendingAdapters;
	
	NSTimer *refreshTimer;
	
	id lastNotifyAdapter;
	
	AdMoGoConfigStore *configStore;
	AMNetworkReachabilityWrapper *rollOverReachability;
	CLLocationManager *locationManager;
    AdMoGoAdNetworkConfig *lastAdNetworkConfig;

    AdViewType adType;
    BOOL expressMode;
    BOOL fetchingNewConfig;
    BOOL haveCache;
    BOOL AdFirstRequested;
    BOOL isTimerUpdateString;
}

+ (AdMoGoView *)requestAdMoGoViewWithDelegate:(id<AdMoGoDelegate>)delegate AndAdType:(AdViewType)type;
+ (AdMoGoView *)requestAdMoGoViewWithDelegate:(id<AdMoGoDelegate>)delegate AndAdType:(AdViewType)type ExpressMode:(BOOL)express;

+ (CLLocation *)sharedLocation;

/**
 * Different ad networks may return different ad sizes. You may adjust the size
 * of the AdMoGoView and your UI to avoid unsightly borders or chopping off
 * pixels from ads. Call this method when you receive the adMoGoDidReceiveAd
 * delegate method to get the size of the underlying ad network ad.
 */
- (CGSize)actualAdSize;

- (void)pauseAdRequest;
- (void)resumeAdRequest;

/**
 * Some ad networks may offer different banner sizes for different orientations.
 * Call this function when the orientation of your UI changes so the underlying
 * ad may handle the orientation change properly. You may also want to
 * call the actualAdSize method right after calling this to get the size of
 * the ad after the orientation change.
 */
- (void)rotateToOrientation:(UIInterfaceOrientation)orientation;



/**
 * You can set the delegate to nil or another object.
 * Make sure you set the delegate to nil when you release an AdMoGoView
 * instance to avoid the AdMoGoView from calling to a non-existent delegate.
 * If you set the delegate to another object, note that if the new delegate
 * returns a different value for adMoGoApplicationKey, it will not overwrite
 * the application key provided by the delegate you supplied for
 * +requestAdMoGoViewWithDelegate .
 */
@property (nonatomic, assign) IBOutlet id<AdMoGoDelegate> delegate;
@property (nonatomic,assign) AdViewType adType;
@property (nonatomic,assign) BOOL expressMode;
#pragma mark For ad network adapters use only
/**
 * Called by Adapters when there's get a new ad view. Whether or not receive
 */
- (void)adapter:(AdMoGoAdNetworkAdapter *)adapter didGetAd:(NSString *)adType;

/**
 * Called by Adapters when there's a new ad view.
 */
- (void)adapter:(AdMoGoAdNetworkAdapter *)adapter didReceiveAdView:(UIView *)view;

/**
 * Called by Adapters when ad view failed.
 */
- (void)adapter:(AdMoGoAdNetworkAdapter *)adapter didFailAd:(NSError *)error;

/**
 * Called by Adapters when the ad request is finished, but the ad view is
 * furnished elsewhere. e.g. Generic Notification
 */
- (void)adapterDidFinishAdRequest:(AdMoGoAdNetworkAdapter *)adapter;

-(void)AdMoGoBaiduI:(NSString *)nid netType:(AdMoGoAdNetworkType)type;
-(void)AdMoGoBaiduC:(NSString *)nid netType:(AdMoGoAdNetworkType)type;
@end