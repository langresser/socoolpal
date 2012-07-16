//
//  File: AdMoGoAdNetworkAdapter.h
//  Project: AdsMOGO iOS SDK
//  Version: 1.1.9
//
//  Copyright 2011 AdsMogo.com. All rights reserved.
//

#import "AdMoGoDelegateProtocol.h"
#import "AdMoGoConfig.h"

typedef enum {
	AdMoGoAdNetworkTypeAdMob             = 1,
	AdMoGoAdNetworkTypeJumpTap           = 2,
	AdMoGoAdNetworkTypeVideoEgg          = 3,
	AdMoGoAdNetworkTypeMedialets         = 4,
	AdMoGoAdNetworkTypeLiveRail          = 5,
	AdMoGoAdNetworkTypeMillennial        = 6,
	AdMoGoAdNetworkTypeGreyStripe        = 7,
	AdMoGoAdNetworkTypeQuattro           = 8,
	AdMoGoAdNetworkTypeCustom            = 9,
	AdMoGoAdNetworkTypeAdMoGo10          = 10,
	AdMoGoAdNetworkTypeMobClix           = 11,
	AdMoGoAdNetworkTypeMdotM             = 12,
	AdMoGoAdNetworkTypeAdMoGo13          = 13,
	AdMoGoAdNetworkTypeGoogleAdSense     = 14,
	AdMoGoAdNetworkTypeGoogleDoubleClick = 15,
	AdMoGoAdNetworkTypeGeneric           = 16,
	AdMoGoAdNetworkTypeEvent             = 17,
	AdMoGoAdNetworkTypeInMobi            = 18,
	AdMoGoAdNetworkTypeIAd               = 19,
	AdMoGoAdNetworkTypeZestADZ           = 20,
	
	AdMoGoAdNetworkTypeAdChina      = 21,
	AdMoGoAdNetworkTypeWiAd         = 22,
	AdMoGoAdNetworkTypeWooboo       = 23,
	AdMoGoAdNetworkTypeYouMi        = 24,
	AdMoGoAdNetworkTypeCasee        = 25,
	AdMoGoAdNetworkTypeSmartMAD     = 26,
	AdMoGoAdNetworkTypeMoGo         = 27,
    AdMoGoAdNetworkTypeAdTouch      = 28,
    AdMoGoAdNetworkTypeDoMob        = 29,
    AdMoGoAdNetworkTypeAdOnCN       = 30,
    AdMoGoAdNetworkTypeMobiSage     = 31,
    AdMoGoAdNetworkTypeAirAd        = 32,
    AdMoGoAdNetworkTypeAdwo         = 33,
    AdMoGoAdNetworkTypeSmaato       = 35,
    AdMoGoAdNetworkTypeIZP          = 40,
    AdMoGoAdNetworkTypeBaiduMobAd   = 44,
    AdMoGoAdNetworkTypeExchange     = 45,
    AdMoGoAdNetworkTypePremiumAD    = 48,
    AdMoGoAdNetworkTypeAdFractal    = 50,
    AdMoGoAdNetworkTypeSuiZong      = 51,
    AdMoGoAdNetworkTypeWinsAd       = 52,
    AdMoGoAdNetworkTypeMobWinAd     = 53,
    AdMoGoAdNetworkTypeRecommendAD  = 54,
    AdMoGoAdNetworkTypeUM           = 55,
    AdMoGoAdNetworkTypeWQ           = 56,
    AdMoGoAdNetworkTypeAdermob      = 57,
    
    AdMoGoAdNetworkTypeAdChinaFullAd = 1021,
    AdMoGoAdNetworkTypeYouMiFullAd  = 1024,
    
} AdMoGoAdNetworkType;

@class AdMoGoView;
@class AdMoGoConfig;
@class AdMoGoAdNetworkConfig;

@interface AdMoGoAdNetworkAdapter : NSObject {
	id<AdMoGoDelegate> adMoGoDelegate;
	AdMoGoView *adMoGoView;
	AdMoGoConfig *adMoGoConfig;
	AdMoGoAdNetworkConfig *networkConfig;
	UIView *adNetworkView;
}

- (id)initWithAdMoGoDelegate:(id<AdMoGoDelegate>)delegate
						view:(AdMoGoView *)view
					  config:(AdMoGoConfig *)config
			   networkConfig:(AdMoGoAdNetworkConfig *)netConf;

- (void)getAd;
- (void)stopBeingDelegate;
- (void)stopTimer;

- (BOOL)shouldSendExMetric;
- (BOOL)shouldSendExRequest;

- (void)rotateToOrientation:(UIInterfaceOrientation)orientation;

- (BOOL)isBannerAnimationOK:(AMBannerAnimationType)animType;

@property (nonatomic,assign) id<AdMoGoDelegate> adMoGoDelegate;
@property (nonatomic,assign) AdMoGoView *adMoGoView;
@property (nonatomic,retain) AdMoGoConfig *adMoGoConfig;
@property (nonatomic,retain) AdMoGoAdNetworkConfig *networkConfig;
@property (nonatomic,retain) UIView *adNetworkView;

@end