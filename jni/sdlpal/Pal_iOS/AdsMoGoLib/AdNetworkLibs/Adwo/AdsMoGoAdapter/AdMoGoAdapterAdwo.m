//
//  File: AdMoGoAdapterAdwo.m
//  Project: AdsMOGO iOS SDK
//  Version: 1.1.9
//
//  Copyright 2011 AdsMogo.com. All rights reserved.
//

#import "AdMoGoAdapterAdwo.h"
#import "AdMoGoView.h"
#import "AdMoGoAdNetworkRegistry.h"
#import "AdMoGoAdNetworkAdapter+Helpers.h"
#import "AdMoGoAdNetworkConfig.h" 

@implementation AdMoGoAdapterAdwo

+ (AdMoGoAdNetworkType)networkType {
	return AdMoGoAdNetworkTypeAdwo;
}

+ (void)load {
	[[AdMoGoAdNetworkRegistry sharedRegistry] registerClass:self];
}

- (void)getAd{
    [adMoGoView adapter:self didGetAd:@"adwo"];
    
    NSInteger isTest = 1;
    if (networkConfig.testMode) {
        isTest = 0;
    }
    
    timer = [[NSTimer scheduledTimerWithTimeInterval:10 target:self selector:@selector(loadAdTimeOut:) userInfo:nil repeats:NO] retain];
    
    if (adMoGoView.adType == AdViewTypeNormalBanner) {
        AWAdView *awAdView = [[AWAdView alloc] initWithAdwoPid:networkConfig.pubId adIdType:1 adTestMode:isTest adSizeForPad:ADWO_ADS_BANNER_SIZE_FOR_IPAD_320x50];
        awAdView.delegate = self;
        awAdView.adRequestTimeIntervel = 600;
        awAdView.userGpsEnabled = NO;
        [awAdView loadAd];
        self.adNetworkView = awAdView;
        [awAdView release];
    }
    else if (adMoGoView.adType == AdViewTypeLargeBanner) {
        AWAdView *awAdView = [[AWAdView alloc] initWithAdwoPid:networkConfig.pubId adIdType:1 adTestMode:isTest adSizeForPad:ADWO_ADS_BANNER_SIZE_FOR_IPAD_720x110];
        awAdView.delegate = self;
        awAdView.adRequestTimeIntervel = 600;
        awAdView.userGpsEnabled = NO;
        [awAdView loadAd];
        self.adNetworkView = awAdView;
        [awAdView release];
    }
}

- (void)stopBeingDelegate {
	AWAdView *adView = (AWAdView *)self.adNetworkView;
    if(adView != nil)
    {
        adView.delegate = nil;
        [adView killTimer];
    }
}

- (void)stopTimer {
    if (timer) {
        [timer invalidate];
        [timer release];
        timer = nil;
    }
}

- (void)dealloc {
    if (timer) {
        [timer invalidate];
        [timer release];
        timer = nil;
    }
	[super dealloc];
}

#pragma mark implement AWDelegate method
- (UIViewController *)viewControllerForPresentingModalView{
    return [adMoGoDelegate viewControllerForPresentingModalView];
}

- (void)adViewDidFailToLoadAd:(AWAdView *)view{
    if (timer) {
        [timer invalidate];
        [timer release];
        timer = nil;
    }
    [adMoGoView adapter:self didFailAd:nil];
}

- (void)adViewDidLoadAd:(AWAdView *)view{
    if (timer) {
        [timer invalidate];
        [timer release];
        timer = nil;
    }
    [adMoGoView adapter:self didReceiveAdView:view];
}

- (void)willPresentModalViewForAd:(AWAdView *)view{
    [self helperNotifyDelegateOfFullScreenModal];
}

- (void)didDismissModalViewForAd:(AWAdView *)view{
    [self helperNotifyDelegateOfFullScreenModalDismissal];
}

- (void)loadAdTimeOut:(NSTimer*)theTimer {
    if (timer) {
        [timer invalidate];
        [timer release];
        timer = nil;
    }
    [self stopBeingDelegate];
    [adMoGoView adapter:self didFailAd:nil];
}
@end