//
//  File: AdMoGoAdapterDoMob.h
//  Project: AdsMOGO iOS SDK
//  Version: 1.1.9
//
//  Copyright 2011 AdsMogo.com. All rights reserved.
//Domob v2.0

#import "AdMoGoAdNetworkAdapter.h"
#import "DMAdView.h"

@interface AdMoGoAdapterDoMob : AdMoGoAdNetworkAdapter <DMAdViewDelegate>{
    NSTimer *timer;
}
+ (AdMoGoAdNetworkType)networkType;
- (void)loadAdTimeOut:(NSTimer*)theTimer;
@end
