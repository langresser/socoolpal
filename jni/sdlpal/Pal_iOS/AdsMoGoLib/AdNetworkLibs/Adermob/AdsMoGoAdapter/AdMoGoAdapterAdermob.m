//
//  AdMoGoAdapterAdermob.m
//  AdsMogo   
//  Version: 1.1.9
//  Created by pengxu on 12-4-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.

#import "AdMoGoAdapterAdermob.h"
#import "AdMoGoAdNetworkRegistry.h"
#import "AdMoGoView.h"
#import "AdMoGoAdNetworkConfig.h"

@implementation AdMoGoAdapterAdermob

+ (AdMoGoAdNetworkType)networkType {
	return AdMoGoAdNetworkTypeAdermob;
}

+ (void)load {
	[[AdMoGoAdNetworkRegistry sharedRegistry] registerClass:self];
}

- (void)getAd {
    CGRect adFrame = CGRectMake(0, 0, 320, 50);
    AdViewType type = adMoGoView.adType;
    switch (type) {
        case AdViewTypeNormalBanner:
            adFrame = CGRectMake(0, 0, 320, 50);
            break;
        case AdViewTypeLargeBanner:
            adFrame = CGRectMake(0, 0, 728, 90);
            break;
        default:
            [adMoGoView adapter:self didGetAd:@"adermob"];
            [adMoGoView adapter:self didFailAd:nil];
            return;
            break;
    }
    
    UIView *view = [[UIView alloc] initWithFrame:CGRectMake(0, 0, adFrame.size.width, adFrame.size.height)];
    [AderSDK stopAdService];
    [AderSDK startAdService:view appID:networkConfig.pubId adFrame:adFrame model:MODEL_RELEASE];
    [AderSDK setDelegate:self];
    self.adNetworkView = view;
}

- (void)stopBeingDelegate{
    [AderSDK setDelegate:nil];
}
- (void)dealloc {
	[super dealloc];
}

- (void)didSucceedToReceiveAd:(NSInteger)count {
    [adMoGoView adapter:self didGetAd:@"adermob"];
    [adMoGoView adapter:self didReceiveAdView:adNetworkView];
}

- (void) didReceiveError:(NSError *)error {
    [adMoGoView adapter:self didGetAd:@"adermob"];
    [adMoGoView adapter:self didFailAd:nil];
}


@end
