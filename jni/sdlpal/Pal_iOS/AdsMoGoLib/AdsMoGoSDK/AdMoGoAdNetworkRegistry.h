//
//  File: AdMoGoAdNetworkRegistry.h
//  Project: AdsMOGO iOS SDK
//  Version: 1.1.9
//
//  Copyright 2011 AdsMogo.com. All rights reserved.
//

#import <Foundation/Foundation.h>

@class AdMoGoAdNetworkAdapter;
@class AdMoGoClassWrapper;

@interface AdMoGoAdNetworkRegistry : NSObject {
	NSMutableDictionary *adapterDict;
}

+ (AdMoGoAdNetworkRegistry *)sharedRegistry;
- (void)registerClass:(Class)adapterClass;
- (AdMoGoClassWrapper *)adapterClassFor:(NSInteger)adNetworkType;

@end