//  AdMoGoAdapterMobWinAd.m
//  Project: AdsMOGO iOS SDK
//  Version: 1.1.9
//  Created by pengxu on 12-3-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.


#import "AdMoGoAdapterMobWinAd.h"
#import "AdMoGoAdNetworkRegistry.h"
#import "AdMoGoView.h"
#import "AdMoGoAdNetworkConfig.h" 
#import "AdMoGoAdNetworkAdapter+Helpers.h"
#import "MobWinBannerViewDelegate.h"

@implementation AdMoGoAdapterMobWinAd

+ (AdMoGoAdNetworkType)networkType {
	return AdMoGoAdNetworkTypeMobWinAd;
}

+ (void)load {
	[[AdMoGoAdNetworkRegistry sharedRegistry] registerClass:self];
}

- (void)getAd {
    AdViewType type = adMoGoView.adType;
    CGSize size =CGSizeMake(0, 0);
    MobWinBannerSizeIdentifier mobwinSizeID;
    switch (type) {
        case AdViewTypeNormalBanner:
        case AdViewTypeiPadNormalBanner:
            mobwinSizeID = MobWINBannerSizeIdentifier320x50;
            size =CGSizeMake(320, 50);
            break;
        case AdViewTypeRectangle:
            mobwinSizeID = MobWINBannerSizeIdentifier300x250;
            size =CGSizeMake(300, 250);
            break;
        case AdViewTypeMediumBanner:
            mobwinSizeID = MobWINBannerSizeIdentifier468x60;
            size =CGSizeMake(468, 60);
            break;
        case AdViewTypeLargeBanner:
            mobwinSizeID = MobWINBannerSizeIdentifier728x90;
            size =CGSizeMake(728, 90);
            break;
        default:
            break;
    }
    for (UIView *view in [self.adMoGoView subviews]) {
        if ([view isKindOfClass:[MobWinBannerView class]]) {
            MobWinBannerView *laseAdView = (MobWinBannerView*)view;
            [laseAdView stopRequest];
        }
    }
    
    adView = [[MobWinBannerView alloc] initMobWinBannerSizeIdentifier:mobwinSizeID keyByMobWIN:@"ior0224ace"];
    adView.adUnitID = networkConfig.pubId;

    adView.rootViewController = [adMoGoDelegate viewControllerForPresentingModalView];

    adView.delegate = self;

    [adView startRequest];
    
//    timer = [[NSTimer scheduledTimerWithTimeInterval:10 target:self selector:@selector(loadAdTimeOut:) userInfo:nil repeats:NO] retain];

    self.adNetworkView = adView;
}

- (void)dealloc {
//    if (timer) {
//        [timer invalidate];
//        [timer release];
//        timer = nil;
//    }
	[super dealloc];
}
- (void)bannerViewDidReceived{
//    if (timer) {
//        [timer invalidate];
//        [timer release];
//        timer = nil;
//    }
    [adMoGoView adapter:self didGetAd:@"mobwin"];
    [adMoGoView adapter:self didReceiveAdView:adNetworkView];
}
- (void)bannerViewFailToReceived{
//    if (timer) {
//        [timer invalidate];
//        [timer release];
//        timer = nil;
//    }
    [adMoGoView adapter:self didGetAd:@"mobwin"];
    [adMoGoView adapter:self didFailAd:nil];
}
//- (void)loadAdTimeOut:(NSTimer*)theTimer {
//    if (timer) {
//        [timer invalidate];
//        [timer release];
//        timer = nil;
//    }
//    [self stopBeingDelegate];
//    [adMoGoView adapter:self didFailAd:nil];
//}
- (void)stopBeingDelegate {
    [adView stopRequest];
    adView.delegate = nil;
}

@end
