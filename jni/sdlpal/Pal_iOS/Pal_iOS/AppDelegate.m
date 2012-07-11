//
//  AppDelegate.m
//  ShenxiandaoHelper
//
//  Created by 王 佳 on 12-2-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AppDelegate.h"

#import "ViewController.h"
#include "SDL.h"

@implementation AppDelegate

@synthesize window;
@synthesize viewController;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    
    self.viewController = [[ViewController alloc] initWithNibName:nil bundle:nil];
    [self.window addSubview:viewController.view];
    [self.window makeKeyAndVisible];
    
    SDL_main(0, 0);

//    [MobClick setLogEnabled:YES];
//    [MobClick setDelegate:self reportPolicy:BATCH];
//    [MobClick updateOnlineConfig];
//    [MobClick checkUpdate];
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
     */
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    /*
     Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
     */
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    SDL_SendQuit();
    /* hack to prevent automatic termination.  See SDL_uikitevents.m for details */
}

- (void) applicationDidBecomeActive:(UIApplication*)application
{
    //NSLog(@"%@", NSStringFromSelector(_cmd));
    
    // Send every window on every screen a RESTORED event.
}

// 自定义appUpdate的实现
- (void)appUpdate:(NSDictionary *)appInfo {
//    if ([[appInfo objectForKey:@"update"] isEqualToString:@"YES"]) {
//        ignoreUpdateFlag = [[NSString alloc]initWithFormat:@"UpadateFlag%@", [appInfo objectForKey:@"version"]];
//        self.appStoreURL = [appInfo objectForKey:@"path"];
//        BOOL ignore = [[NSUserDefaults standardUserDefaults]boolForKey:ignoreUpdateFlag];
//        
//        if (!ignore) {
//            self.backupInfo = appInfo;
//            // 防止网络阻塞
//            [self performSelectorOnMainThread:@selector(showUpdateView:) withObject:backupInfo waitUntilDone:YES];
//        }
//    }
}

-(void)showUpdateView:(NSDictionary*) appInfo{
//    UIAlertView* alert = [[UIAlertView alloc]initWithTitle:[NSString stringWithFormat:@"有可用的新版本%@", [appInfo objectForKey:@"version"]] message:[appInfo objectForKey:@"update_log"] delegate:self cancelButtonTitle:@"下次再说" otherButtonTitles:@"访问App Store", @"忽略此版本", nil];
//    [alert show];
//    self.backupInfo = nil;
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
//    if (buttonIndex == 1) {
//        [[UIApplication sharedApplication] openURL:[NSURL URLWithString:self.appStoreURL]];
//    } else if (buttonIndex == 2) {
//        [[NSUserDefaults standardUserDefaults]setBool:YES forKey:ignoreUpdateFlag];
//        [[NSUserDefaults standardUserDefaults]synchronize];
//    } else if (buttonIndex == 0) {
//    }
//
//    self.appStoreURL = nil;
//    self.ignoreUpdateFlag = nil;
}

@end
