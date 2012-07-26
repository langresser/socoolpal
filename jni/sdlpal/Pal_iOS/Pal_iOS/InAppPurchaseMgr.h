//
//  InAppPurchaseMgr.h
//  ShenxiandaoHelper
//
//  Created by 王 佳 on 12-3-18.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>

#define kRemoveAdsId @"com.bananastudio.pal98.hack"

#define kIAPFailedNotification @"kIAPTransactionFailedNotification"
#define kIAPSucceededNotification @"kIAPTransactionSucceededNotification"

#define kRemoveAdsFlag @"bsrmads"
#define kRemoveReceiptFlag @"proUpgradeTransactionReceipt"

@interface InAppPurchaseMgr : NSObject<SKPaymentTransactionObserver>
{
    SKProduct *proUpgradeProduct;
    SKProductsRequest *productsRequest;
}

+(InAppPurchaseMgr*)sharedInstance;
// public methods
- (void)loadStore;
- (BOOL)canMakePurchases;
- (void)purchaseProUpgrade;
@end
