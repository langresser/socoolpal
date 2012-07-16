//
//  File: AdMoGoAdapterYouMi.m
//  Project: AdsMOGO iOS SDK
//  Version: 1.1.9
//
//  Copyright 2011 AdsMogo.com. All rights reserved.
//

#import "AdMoGoAdapterYouMi.h"
#import "YouMiView.h"
#import "AdMoGoView.h"
#import "AdMoGoAdNetworkRegistry.h"
#import "AdMoGoAdNetworkAdapter+Helpers.h"
#import "AdMoGoAdNetworkConfig.h"

#define kAdMoGoYoumiAppIDKey @"AppID"
#define kAdMoGoYoumiAppSecretKey @"AppSecret"

@implementation AdMoGoAdapterYouMi

+ (AdMoGoAdNetworkType)networkType {
	return AdMoGoAdNetworkTypeYouMi;
}

+ (void)load {
	[[AdMoGoAdNetworkRegistry sharedRegistry] registerClass:self];
}

- (void)getAd {
	[adMoGoView adapter:self didGetAd:@"youmi"];
	
    AdViewType type = adMoGoView.adType;
    YouMiBannerContentSizeIdentifier youMiSizeID;
    switch (type) {
        case AdViewTypeNormalBanner:
        case AdViewTypeiPadNormalBanner:
            youMiSizeID = YouMiBannerContentSizeIdentifier320x50;
            break;
        case AdViewTypeRectangle:
            youMiSizeID = YouMiBannerContentSizeIdentifier300x250;
            break;
        case AdViewTypeMediumBanner:
            youMiSizeID = YouMiBannerContentSizeIdentifier468x60;
            break;
        case AdViewTypeLargeBanner:
            youMiSizeID = YouMiBannerContentSizeIdentifier728x90;
            break;
        default:
            break;
    }
    
    timer = [[NSTimer scheduledTimerWithTimeInterval:10 target:self selector:@selector(loadAdTimeOut:) userInfo:nil repeats:NO] retain];
    
    YouMiView *adView = [[YouMiView alloc] initWithContentSizeIdentifier:youMiSizeID
                                                                delegate:self];
    [YouMiView setShouldCacheImage:YES];
    [YouMiView setShouldGetLocation:NO];
    adView.appID = [networkConfig.credentials objectForKey:kAdMoGoYoumiAppIDKey];
    adView.appSecret = [networkConfig.credentials objectForKey:kAdMoGoYoumiAppSecretKey];
    if (networkConfig.testMode) {
        adView.testing = YES;
    }
    else {
        adView.testing = NO;
    }
    adView.indicateBackgroundColor = [self helperBackgroundColorToUse];
    adView.textColor = [self helperTextColorToUse];
    adView.indicateRounded = YES;
    [adView start];
    self.adNetworkView = adView;
    [adView release];
}

- (void)stopBeingDelegate {
	YouMiView *adView = (YouMiView *)adNetworkView;
	if (adView != nil) {
		adView.delegate = nil;
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

#pragma mark YouMiView Delegate 
- (void)didReceiveAd:(YouMiView *)adView {
    if (timer) {
        [timer invalidate];
        [timer release];
        timer = nil;
    }
    [adMoGoView adapter:self didReceiveAdView:adView];
}

- (void)didFailToReceiveAd:(YouMiView *)adView  error:(NSError *)error {
    if (timer) {
        [timer invalidate];
        [timer release];
        timer = nil;
    }
    [adMoGoView adapter:self didFailAd:error];
}

- (void)didPresentScreen:(YouMiView *)adView {
    [self helperNotifyDelegateOfFullScreenModal];
}

- (void)didDismissScreen:(YouMiView *)adView {
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