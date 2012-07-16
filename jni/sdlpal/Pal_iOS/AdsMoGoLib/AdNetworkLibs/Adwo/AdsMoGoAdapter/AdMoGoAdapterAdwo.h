//
//  File: AdMoGoAdapterAdwo.h
//  Project: AdsMOGO iOS SDK
//  Version: 1.1.9
//
//  Copyright 2011 AdsMogo.com. All rights reserved.
//Adwo v2.5.2

#import "AdMoGoAdNetworkAdapter.h"
#import "AWAdView.h"
//#import "AWInterstitialAdController.h"

@interface AdMoGoAdapterAdwo : AdMoGoAdNetworkAdapter <AWAdViewDelegate/*AWInterstitialAdControllerDelegate*/> {
    NSTimer *timer;
    
    BOOL haveTab;
}
- (void)loadAdTimeOut:(NSTimer*)theTimer;
@end
