//
//  File: AdMoGoAdNetworkAdapter＋Helpers.h
//  Project: AdsMOGO iOS SDK
//  Version: 1.1.9
//
//  Copyright 2011 AdsMogo.com. All rights reserved.
//

#import "AdMoGoAdNetworkAdapter.h"

@interface AdMoGoAdNetworkAdapter (Helpers)

- (void)helperNotifyDelegateOfFullScreenModal;
- (void)helperNotifyDelegateOfFullScreenModalDismissal;

- (void)helperNotifyDelegateOfFullScreenAdModal;
- (void)helperNotifyDelegateOfFullScreenAdModalDismissal;

- (UIColor *)helperBackgroundColorToUse;
- (UIColor *)helperTextColorToUse;
- (UIColor *)helperSecondaryTextColorToUse;
- (NSInteger)helperCalculateAge;
@end