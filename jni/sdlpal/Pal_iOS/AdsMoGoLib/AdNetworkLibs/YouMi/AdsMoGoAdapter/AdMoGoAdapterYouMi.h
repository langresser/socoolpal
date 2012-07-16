//
//  File: AdMoGoAdapterYouMi.h
//  Project: AdsMOGO iOS SDK
//  Version: 1.1.9
//
//  Copyright 2011 AdsMogo.com. All rights reserved.
//
//YouMi v3.0 20110726

#import "AdMoGoAdNetworkAdapter.h"
#import "YouMiDelegateProtocol.h"

@class YouMiView;
@protocol YouMiDelegate;

@interface AdMoGoAdapterYouMi : AdMoGoAdNetworkAdapter <YouMiDelegate> {
	NSTimer *timer;
}
+ (AdMoGoAdNetworkType)networkType;
- (void)loadAdTimeOut:(NSTimer*)theTimer;
@end
