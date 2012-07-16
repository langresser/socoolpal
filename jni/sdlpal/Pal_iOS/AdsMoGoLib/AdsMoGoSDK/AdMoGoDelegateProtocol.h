//
//  File: AdMoGoDelegateProtocol.h
//  Project: AdsMOGO iOS SDK
//  Version: 1.1.9
//
//  Copyright 2011 AdsMogo.com. All rights reserved.
//

#import <CoreLocation/CoreLocation.h>
#import <UIKit/UIKit.h>

@class AdMoGoView;

@protocol AdMoGoDelegate<NSObject>

@required

- (NSString *)adMoGoApplicationKey;
- (UIViewController *)viewControllerForPresentingModalView;

@optional

#pragma mark notifications
/**
 * You can get notified when the user receive the ad
 */
- (void)adMoGoDidReceiveAd:(AdMoGoView *)adMoGoView;
/**
 *You can get notified when the user delete the ad 
 */
- (void)adMoGoDeleteAd:(AdMoGoView *)adMoGoView;
/**
 * You can get notified when the user failed receive the ad
 */
- (void)adMoGoDidFailToReceiveAd:(AdMoGoView *)adMoGoView usingBackup:(BOOL)yesOrNo;

/**
 
 * These notifications will let you know when a user is being shown a full screen
 * webview canvas with an ad because they tapped on an ad.  You should listen to
 * these notifications to determine when to pause/resume your game--if you're
 * building a game app.
 */
- (void)adMoGoWillPresentFullScreenModal;
- (void)adMoGoDidDismissFullScreenModal;

/*Full Screen Notifications*/
- (void)adMoGoFullScreenAdReceivedRequest;
- (void)adMoGoFullScreenAdFailed;
- (void)adMoGoWillPresentFullScreenAdModal;
- (void)adMoGoDidDismissFullScreenAdModal;

#pragma mark behavior configurations
/**
 * Request test ads for APIs that supports it. Make sure you turn it to OFF
 * or remove the function before you submit your app to the app store.
 */
- (BOOL)adMoGoTestMode DEPRECATED_ATTRIBUTE;


#pragma mark demographic information optional delegate methods
- (NSString *)phoneNumber; // user's phone number
- (CLLocation *)locationInfo; // user's current location
- (NSString *)postalCode; // user's postal code, e.g. "94401"
- (NSString *)areaCode; // user's area code, e.g. "415"
- (NSDate *)dateOfBirth; // user's date of birth
- (NSString *)gender; // user's gender (e.g. @"m" or @"f")
- (NSString *)keywords; // keywords the user has provided or that are contextually relevant, e.g. @"twitter client iPhone"
- (NSString *)searchString; // a search string the user has provided, e.g. @"Jasmine Tea House San Francisco"
- (NSUInteger)incomeLevel; // return actual annual income

@end