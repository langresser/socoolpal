//
//  iOSUtil.m
//  Pal_iOS
//
//  Created by 王 佳 on 12-7-16.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
#import <Foundation/Foundation.h>
#include "main.h"

#import "video/uikit/SDL_uikitwindow.h"
#import "MobClick.h"
#import "UMFeedback.h"
#import "CGJoystick.h"
#import "CGJoystickButton.h"
#import "SystemView.h"
#import "AppDelegate.h"

#ifndef APP_FOR_APPSTORE
#import <DianJinOfferPlatform/DianJinOfferPlatform.h>
#import <DianJinOfferPlatform/DianJinOfferBanner.h>
#import <DianJinOfferPlatform/DianJinBannerSubViewProperty.h>
#import <DianJinOfferPlatform/DianJinTransitionParam.h>
#endif

extern BOOL g_useJoyStick;
extern int g_currentMB;

int isPad()
{
	BOOL result = NO;
	if ([[UIDevice currentDevice] respondsToSelector:@selector(userInterfaceIdiom)]) {
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= 30200
		result = ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPad);
#endif
	}
	return result;
}

extern char g_application_dir[256];
extern char g_resource_dir[256];
void initDir()
{
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString  *plistPath = [paths objectAtIndex:0];
    strlcpy(g_resource_dir, [plistPath UTF8String], sizeof(g_resource_dir));
    
    g_resource_dir[strlen(g_resource_dir)] = '/';
}

void getFileStatus(const char* pszName)
{
    NSFileManager* fmgr = [NSFileManager defaultManager];
    if (!fmgr) {
        return;
    }
    
    NSError* error;
    NSDictionary* attr = [fmgr attributesOfItemAtPath:[NSString stringWithUTF8String:pszName] error:&error];


    NSLog(@"file: %s    attr:%@ ", pszName, attr);
}

void getScreenSize(int* width, int* height)
{
    CGSize size = [UIScreen mainScreen].bounds.size;
    if (width) {
        *width = size.width > size.height ? size.width : size.height;
    }
    
    if (height) {
        *height = size.width > size.height ? size.height : size.width;
    }
}

void showJoystick()
{
    if (!g_useJoyStick) {
        return;
    }

    GameViewController* vc = (GameViewController*)((SDLUIKitDelegate*)[SDLUIKitDelegate sharedAppDelegate]).viewController;
    [vc showJoystick];
}

void hideJoystick()
{
    GameViewController* vc = (GameViewController*)((SDLUIKitDelegate*)[SDLUIKitDelegate sharedAppDelegate]).viewController;
    [vc hideJoystick];
}

void showMenu()
{
    GameViewController* vc = (GameViewController*)((SDLUIKitDelegate*)[SDLUIKitDelegate sharedAppDelegate]).viewController;
    [vc showGameMenu];
    [vc showSearchButton];
}

void hideMenu()
{
    GameViewController* vc = (GameViewController*)((SDLUIKitDelegate*)[SDLUIKitDelegate sharedAppDelegate]).viewController;
    [vc hideGameMenu];
    [vc hideSearchButton];
}

void showBackButton()
{
    GameViewController* vc = (GameViewController*)((SDLUIKitDelegate*)[SDLUIKitDelegate sharedAppDelegate]).viewController;
    [vc showBackButton];
}

void hideSearchButton()
{
    GameViewController* vc = (GameViewController*)((SDLUIKitDelegate*)[SDLUIKitDelegate sharedAppDelegate]).viewController;
    [vc hideSearchButton];
}

void hideBackButton()
{
    GameViewController* vc = (GameViewController*)((SDLUIKitDelegate*)[SDLUIKitDelegate sharedAppDelegate]).viewController;
    [vc hideBackButton];
}
