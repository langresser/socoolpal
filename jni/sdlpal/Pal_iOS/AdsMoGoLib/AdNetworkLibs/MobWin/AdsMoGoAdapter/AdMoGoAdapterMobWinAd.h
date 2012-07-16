//
//  AdMoGoAdapterMobWinAd.h
//  Project: AdsMOGO iOS SDK
//  Version: 1.1.9
//  Created by pengxu on 12-3-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AdMoGoAdNetworkAdapter.h"
#import "MobWinBannerViewDelegate.h"
#import "MobWinBannerView.h"


@interface AdMoGoAdapterMobWinAd : AdMoGoAdNetworkAdapter <MobWinBannerViewDelegate>{
    MobWinBannerView *adView;
//    NSTimer *timer;
}
+ (AdMoGoAdNetworkType)networkType;
//- (void)loadAdTimeOut:(NSTimer*)theTimer;
@end
