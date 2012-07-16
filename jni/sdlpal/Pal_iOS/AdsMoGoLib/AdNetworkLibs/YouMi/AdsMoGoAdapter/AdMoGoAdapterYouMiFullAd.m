//
//  File: AdMoGoAdapterYouMiFullAd.m
//  Project: AdsMOGO iOS SDK
//  Version: 1.1.9
//
//  Copyright 2011 AdsMogo.com. All rights reserved.
//

#import "AdMoGoAdapterYouMiFullAd.h"
#import "AdMoGoView.h"
#import "AdMoGoAdNetworkRegistry.h"
#import "AdMoGoAdNetworkAdapter+Helpers.h"
#import "AdMoGoAdNetworkConfig.h"

#define kAdMoGoYoumiAppIDKey @"AppID"
#define kAdMoGoYoumiAppSecretKey @"AppSecret"

@implementation AdMoGoAdapterYouMiFullAd
+ (AdMoGoAdNetworkType)networkType {
	return AdMoGoAdNetworkTypeYouMiFullAd;
}

+ (void)load {
	[[AdMoGoAdNetworkRegistry sharedRegistry] registerClass:self];
}

- (void)getAd {
	[adMoGoView adapter:self didGetAd:@"youmi"];
	
    adSpot = [YouMiSpot sharedAdSpot];
    [YouMiSpot setShouldCacheImage:YES];
    [YouMiSpot setShouldGetLocation:NO];
    adSpot.appID = [networkConfig.credentials objectForKey:kAdMoGoYoumiAppIDKey];
    adSpot.appSecret = [networkConfig.credentials objectForKey:kAdMoGoYoumiAppSecretKey];
    adSpot.delegate = self;
    adSpot.displayFormForRequest = YouMiSpotDisplayFormForRequestLandscapeAndPortrait;
    if (networkConfig.testMode) {
        adSpot.testing = YES;
    }
    else {
        adSpot.testing = NO;
    }
    [[YouMiSpot sharedAdSpot] startAdSpotRequest];
    
    timer = [NSTimer scheduledTimerWithTimeInterval:1 target:self selector:@selector(checkAd) userInfo:nil repeats:YES];
    
     
}

- (void)stopBeingDelegate {
    if (timer) {
        [timer invalidate];
        timer = nil;
    }
	[[YouMiSpot sharedAdSpot] setDelegate:nil];
	adSpot = nil;
}

- (void)stopTimer {
    if (timer) {
        [timer invalidate];
        timer = nil;
    }
}

- (void)dealloc {
    if (timer) {
        [timer invalidate];
        timer = nil;
    }
    [super dealloc];
    adSpot = nil;
}

-(void)checkAd {
	if (adSpot != nil && [adSpot isReadyForShow]) {
		YouMiSpotDisplayForm displayForm = YouMiSpotDisplayFormPortrait;
		YouMiSpotProgressType progressType = 1 + arc4random()%3;
		YouMiSpotPresentType presentType = 1 + arc4random()%5;
		NSString *promptTitle = @"广告也精彩...";
		[adSpot showAdSpotWithDisplayForm:displayForm
							 progressType:progressType
							  presentType:presentType
							  promptTitle:promptTitle];
        if (timer) {
            [timer invalidate];
            timer = nil;
        }
    }
    else {
        maxTime ++;
        if (maxTime == 11) {
            if (timer) {
                [timer invalidate];
                timer = nil;
            }
            [adMoGoView adapter:self didFailAd:nil];
        }
    }
}

// 请求插播广告成功后调用
//
// 详解:当接收服务器返回的插播广告数据成功后调用该函数
- (void)didReceiveSpotAd:(YouMiSpot *)adSpot {
    
}

// 请求插播广告失败后调用
// 
// 详解:当接收服务器返回的插播广告数据失败后调用该函数
- (void)didFailToReceiveSpotAd:(YouMiSpot *)adSpot {
    [adMoGoView adapter:self didFailAd:nil];
}

// 加载插播广告内容成功后调用
//
// 详解:插播广告数据请求成功后，加载插播广告的内容，若成功则调用该函数
- (void)didFinishLoadSpotAd:(YouMiSpot *)adSpot {
    
}

// 加载插播广告内容失败后调用
//
// 详解:插播广告数据请求成功后，加载插播广告的内容，若失败则调用该函数
- (void)didFailToFinishLoadSpotAd:(YouMiSpot *)adSpot {
     [adMoGoView adapter:self didFailAd:nil];
}

#pragma mark Show-Spot Notifications Methods
// 将要显示插播广告前调用
// 
// 详解:将要显示一次插播广告内容前调用该函数
- (void)willShowSpotAd:(YouMiSpot *)adSpot {
    [adMoGoView adapter:self didReceiveAdView:nil];
    [self helperNotifyDelegateOfFullScreenAdModal];
}

// 显示插播广告成功后调用
//
// 详解:显示一次插播广告内容后调用该函数
- (void)didShowSpotAd:(YouMiSpot *)adSpot {
    
}

// 将要关闭插播广告前调用
//
// 详解:插播广告显示完成，将要关闭插播广告前调用该函数
- (void)willDismissSpotAd:(YouMiSpot *)adSpot {
    
}

// 成功关闭插播广告后调用
//
// 详解:插播广告显示完成，关闭插播广告后调用该函数
- (void)didDismissSpotAd:(YouMiSpot *)adSpot {
     [self helperNotifyDelegateOfFullScreenAdModalDismissal];
}
@end