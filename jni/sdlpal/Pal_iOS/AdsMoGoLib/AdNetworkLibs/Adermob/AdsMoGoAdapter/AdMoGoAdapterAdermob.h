//
//  AdMoGoAdapterAdermob.h
//  AdsMogo   
//
//  Created by pengxu on 12-4-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AdMoGoAdNetworkAdapter.h"
#import "AderDelegateProtocal.h"
#import "AderSDK.h"

@interface AdMoGoAdapterAdermob : AdMoGoAdNetworkAdapter <AderDelegateProtocal>{

}

+ (AdMoGoAdNetworkType)networkType;
@end
