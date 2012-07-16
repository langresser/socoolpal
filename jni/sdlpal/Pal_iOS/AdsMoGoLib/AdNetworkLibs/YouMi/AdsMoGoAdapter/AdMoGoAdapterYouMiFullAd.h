//
//  File: AdMoGoAdapterYouMiFullAd.h
//  Project: AdsMOGO iOS SDK
//  Version: 1.1.9
//
//  Copyright 2011 AdsMogo.com. All rights reserved.
//

#import "AdMoGoAdNetworkAdapter.h"
#import "YouMiSpot.h"
#import "YouMiSpotDelegateProtocol.h"

@interface AdMoGoAdapterYouMiFullAd : AdMoGoAdNetworkAdapter <YouMiSpotDelegate>{
    YouMiSpot *adSpot;
    NSTimer *timer;
    NSUInteger maxTime;
}

+ (AdMoGoAdNetworkType)networkType;
- (void)checkAd;
@end
