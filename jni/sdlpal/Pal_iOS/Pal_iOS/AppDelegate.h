//
//  AppDelegate.h
//  ShenxiandaoHelper
//
//  Created by 王 佳 on 12-2-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class ViewController;

@interface AppDelegate : UIResponder <UIApplicationDelegate, UIAlertViewDelegate>
{
    UIWindow *window;
    ViewController *viewController;
}

@property (nonatomic, strong) UIWindow *window;
@property (nonatomic, strong) ViewController *viewController;

@end
