//
//  File: AdMoGoConfig.h
//  Project: AdsMOGO iOS SDK
//  Version: 1.1.9
//
//  Copyright 2011 AdsMogo.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "CJSONDeserializer.h"

@class AdMoGoConfig;
@protocol AdMoGoConfigDelegate<NSObject>

@optional
- (void)adMoGoConfigDidReceiveCacheConfig:(AdMoGoConfig *)config;
- (void)adMoGoConfigDidReceiveOfflineConfig:(AdMoGoConfig *)config;
- (void)adMoGoConfigDidReceiveConfig:(AdMoGoConfig *)config;
- (void)adMoGoConfigDidFail:(AdMoGoConfig *)config error:(NSError *)error;
- (void)adMoGoConfigWillGetLocation:(AdMoGoConfig *)cfg;
- (void)adMoGoConfigDidFail:(AdMoGoConfig *)config;
@end

typedef enum {
	AMBannerAnimationTypeNone           = 0,
	AMBannerAnimationTypeFlipFromLeft   = 1,
	AMBannerAnimationTypeFlipFromRight  = 2,
	AMBannerAnimationTypeCurlUp         = 3,
	AMBannerAnimationTypeCurlDown       = 4,
	AMBannerAnimationTypeSlideFromLeft  = 5,
	AMBannerAnimationTypeSlideFromRight = 6,
	AMBannerAnimationTypeFadeIn         = 7,
	AMBannerAnimationTypeRandom         = 8,
} AMBannerAnimationType;

@class AdMoGoAdNetworkConfig;
@class AdMoGoAdNetworkRegistry;

@interface AdMoGoConfig : NSObject {
	NSString *appKey;
	NSURL *configURL;
    NSURL *szConfigURL;
	
	BOOL adsAreOff;
	NSMutableArray *adNetworkConfigs;
    NSMutableArray *bfAdNetworkConfigs;
	
	UIColor *backgroundColor;
	UIColor *textColor;
	NSTimeInterval refreshInterval;
	BOOL locationOn;
	AMBannerAnimationType bannerAnimationType;
    BOOL improveClick;
    NSUInteger  AdFirst;
    NSUInteger  isCloseAd;
    
    NSMutableDictionary *updateDic;
	
	NSMutableArray *delegates;
	BOOL hasConfig;
    BOOL isEmpty;
	
	AdMoGoAdNetworkRegistry *adNetworkRegistry;
	
	NSString *country_code;
    
    NSUInteger savedAdType;
}

- (id)initWithAppKey:(NSString *)ak delegate:(id<AdMoGoConfigDelegate>)delegate AndAdViewType:(NSUInteger)type;
- (BOOL)parseConfigDic:(NSDictionary *)dic error:(NSError **)error;
- (BOOL)parseConfig:(NSData *)data error:(NSError **)error;
- (BOOL)addDelegate:(id<AdMoGoConfigDelegate>)delegate;
- (BOOL)removeDelegate:(id<AdMoGoConfigDelegate>)delegate;
- (void)notifyDelegatesOfFailure:(NSError *)error;
- (void)notifyDelegatesOfGetLocation;
- (void)notifyDelegatesOfFailureServerDomain;


@property (nonatomic,readonly) NSString *appKey;
@property (nonatomic,readonly) NSURL *configURL;
@property (nonatomic,readonly) NSURL *szConfigURL;

@property (nonatomic,readonly) BOOL hasConfig;
@property (nonatomic) BOOL isEmpty;
@property (nonatomic,readonly) BOOL adsAreOff;
@property (nonatomic,readonly) NSArray *adNetworkConfigs;
@property (nonatomic,readonly) NSArray *bfAdNetworkConfigs;
@property (nonatomic,readonly) UIColor *backgroundColor;
@property (nonatomic,readonly) UIColor *textColor;
@property (nonatomic,readonly) NSTimeInterval refreshInterval;
@property (nonatomic,readonly) BOOL locationOn;
@property (nonatomic,readonly) AMBannerAnimationType bannerAnimationType;
@property (nonatomic,readonly) BOOL improveClick;
@property (nonatomic,readonly) NSUInteger AdFirst;
@property (nonatomic,readonly) NSUInteger isCloseAd;
@property (nonatomic,readonly) NSMutableDictionary *updateDic;

@property (nonatomic,assign) AdMoGoAdNetworkRegistry *adNetworkRegistry;

@property (nonatomic,readonly) NSString* country_code;
@end


// Convenience conversion functions, converts val into native types var.
// val can be NSNumber or NSString, all else will cause function to fail
// On failure, return NO.
BOOL amIntVal(NSInteger *var, id val);
BOOL amFloatVal(CGFloat *var, id val);
BOOL amDoubleVal(double *var, id val);
