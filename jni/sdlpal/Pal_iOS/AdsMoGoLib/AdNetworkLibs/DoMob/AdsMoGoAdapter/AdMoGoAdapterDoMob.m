//
//  File: AdMoGoAdapterDoMob.m
//  Project: AdsMOGO iOS SDK
//  Version: 1.1.9
//
//  Copyright 2011 AdsMogo.com. All rights reserved.
//

#import "AdMoGoAdapterDoMob.h"
#import "AdMoGoView.h"
#import "AdMoGoAdNetworkRegistry.h"
#import "AdMoGoAdNetworkAdapter+Helpers.h"
#import "AdMoGoAdNetworkConfig.h" 

@implementation AdMoGoAdapterDoMob


+ (AdMoGoAdNetworkType)networkType{
    return AdMoGoAdNetworkTypeDoMob;
}

+ (void)load{
    [[AdMoGoAdNetworkRegistry sharedRegistry] registerClass:self];
}

- (void)getAd{
    [adMoGoView adapter:self didGetAd:@"domob"];
    AdViewType type = adMoGoView.adType;
    CGSize size = CGSizeZero;
    switch (type) {
        case AdViewTypeNormalBanner:
            size = DOMOB_AD_SIZE_320x50;
            break;
        case AdViewTypeiPadNormalBanner:
            size = DOMOB_AD_SIZE_320x50;
            break;
        case AdViewTypeMediumBanner:
            size = DOMOB_AD_SIZE_448x80;
            break;
        case AdViewTypeLargeBanner:
            size = DOMOB_AD_SIZE_728x90;
            break;
        default:
            break;
    }
    
    timer = [[NSTimer scheduledTimerWithTimeInterval:10 target:self selector:@selector(loadAdTimeOut:) userInfo:nil repeats:NO] retain];

    
    DMAdView *adview = [[DMAdView alloc] initWithPublisherId:networkConfig.pubId size:size autorefresh:NO];
    adview.rootViewController = [adMoGoDelegate viewControllerForPresentingModalView];
    adview.delegate = self;
    [adview loadAd];
    self.adNetworkView = adview;
   
    [adview release];
}

- (void)stopBeingDelegate{
    DMAdView *domobView = (DMAdView *)self.adNetworkView;
    if(domobView != nil) {
        domobView.delegate = nil;
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

- (void)rotateToOrientation:(UIInterfaceOrientation)orientation{
    
}

#pragma mark DoMob Delegate
- (void)dmAdViewSuccessToLoadAd:(DMAdView *)adView {
    if (timer) {
        [timer invalidate];
        [timer release];
        timer = nil;
    }
    [adMoGoView adapter:self didReceiveAdView:adView];
}
- (void)dmAdViewFailToLoadAd:(DMAdView *)adView withError:(NSError *)error {
    if (timer) {
        [timer invalidate];
        [timer release];
        timer = nil;
    }
    [adMoGoView adapter:self didFailAd:nil];
}

- (void)dmWillPresentModalViewFromAd:(DMAdView *)adView {

}
- (void)dmDidDismissModalViewFromAd:(DMAdView *)adView {
    
}
- (void)dmApplicationWillEnterBackgroundFromAd:(DMAdView *)adView {
    
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