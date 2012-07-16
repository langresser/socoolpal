//
//  File: AdMoGoAdNetworkConfig.h
//  Project: AdsMOGO iOS SDK
//  Version: 1.1.9
//
//  Copyright 2011 AdsMogo.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AdMoGoDelegateProtocol.h"

@class AdMoGoError;
@class AdMoGoAdNetworkRegistry;

@interface AdMoGoAdNetworkConfig : NSObject {
	NSInteger networkType;
	NSString *nid;
	NSString *networkName;
	double trafficPercentage;
	NSInteger priority;
	NSDictionary *credentials;
	Class adapterClass;
    BOOL testMode;
}

- (id)initWithDictionary:(NSDictionary *)adNetConfigDict
       adNetworkRegistry:(AdMoGoAdNetworkRegistry *)registry
                   error:(AdMoGoError **)error;

@property (nonatomic,readonly) NSInteger networkType;
@property (nonatomic,readonly) NSString *nid;
@property (nonatomic,readonly) NSString *networkName;
@property (nonatomic,readonly) double trafficPercentage;
@property (nonatomic,readonly) NSInteger priority;
@property (nonatomic,readonly) NSDictionary *credentials;
@property (nonatomic,readonly) NSString *pubId;
@property (nonatomic,readonly) Class adapterClass;
@property (nonatomic,readonly) BOOL testMode;

@end