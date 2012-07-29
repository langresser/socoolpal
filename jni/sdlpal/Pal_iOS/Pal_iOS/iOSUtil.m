//
//  iOSUtil.m
//  Pal_iOS
//
//  Created by 王 佳 on 12-7-16.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
#if 1
#import <Foundation/Foundation.h>
#include "main.h"

#import "video/uikit/SDL_uikitwindow.h"
#import "AdMoGoView.h"
#import "MobClick.h"
#import "UMFeedback.h"
#import "CGJoystick.h"
#import "CGJoystickButton.h"
#import "SystemView.h"

#ifndef APP_FOR_APPSTORE
#import <DianJinOfferPlatform/DianJinOfferPlatform.h>
#import <DianJinOfferPlatform/DianJinOfferBanner.h>
#import <DianJinOfferPlatform/DianJinBannerSubViewProperty.h>
#import <DianJinOfferPlatform/DianJinTransitionParam.h>
#endif

#define JOYSTICK_NONE 0
#define JOYSTICK_MOVE 1
#define JOYSTICK_BATTLE 2

int g_joystickType = JOYSTICK_NONE;
BOOL g_useJoyStick = YES;

#ifndef APP_FOR_APPSTORE
@interface MyDelegate : NSObject<AdMoGoDelegate, DianJinOfferBannerDelegate>
#else
@interface MyDelegate : NSObject<AdMoGoDelegate>
#endif
{
    UIButton* helpBtn;
    UIButton* btnMenu;
    UIButton* btnSearch;
    
    UIButton* btnBack;  // in battle;

    UITextView* textView;
    BOOL isFAQ;
    
#ifndef APP_FOR_APPSTORE
    DianJinOfferBanner *_banner;
#endif
    
    UIButton* moreApp;
    
    AdMoGoView *adView;
    
    SystemView* systemView;
    
    // joystick
    CGJoystick* joystickBase;
    CGJoystickButton* joystickButton;
}
@property(retain, nonatomic) UIButton* helpBtn;
@property(nonatomic) BOOL isFAQ;

+(MyDelegate*)sharedInstance;
-(void)onClickHelp;

-(void)initAds;
-(void)showAds;
-(void)closeAds;

-(void)showMenuBtn;
-(void)hideMenuBtn;

-(void)showSearchButton;
-(void)hideSearchButton;

-(void)showBackButton;
-(void)hideBackButton;
-(void)onClickBack;

-(void)showJoystick;
-(void)hideJoystick;

-(void)beginAutoSave;
@end

MyDelegate* g_delegate = nil;

@implementation MyDelegate
@synthesize helpBtn, isFAQ;
-(void)showMenuBtn
{
    if (btnMenu == nil) {
        btnMenu = [UIButton buttonWithType:UIButtonTypeRoundedRect];
        btnMenu.frame = CGRectMake(430, 296, 60, 24);
        [btnMenu setTitle:@"菜单" forState:UIControlStateNormal];
        [btnMenu setTitle:@"菜单" forState:UIControlStateHighlighted];
        btnMenu.alpha = 0.5;
        [btnMenu addTarget:self action:@selector(onClickMenu) forControlEvents:UIControlEventTouchUpInside];
        
        SDL_Window* window = SDL_GetWindowFromID(g_windowId);
        if (!window) {
            return;
        }
        
        SDL_WindowData* windowData = (SDL_WindowData*)window->driverdata;
        UIView* mainView = windowData->viewcontroller.view;
        [mainView addSubview:btnMenu];
        
        btnSearch = [[UIButton alloc]initWithFrame:CGRectMake(415, 220, 50, 50)];
        [btnSearch setImage:[UIImage imageNamed:@"search"] forState:UIControlStateNormal];
        [btnSearch setImage:[UIImage imageNamed:@"search2"] forState:UIControlStateHighlighted];
        [btnSearch addTarget:self action:@selector(onClickSearch) forControlEvents:UIControlEventTouchUpInside];
        [mainView addSubview:btnSearch];
    }
    
    if (btnMenu.hidden == YES) {
        btnMenu.hidden = NO;
    }

    if (btnSearch.hidden == YES) {
        btnSearch.hidden = NO;
    }
}

-(void)hideMenuBtn
{
    if (!btnMenu || btnMenu.hidden == YES) {
        return;
    }
    
    btnMenu.hidden = YES;
    
    if (!btnSearch || btnSearch.hidden == YES) {
        return;
    }
    btnSearch.hidden = YES;
    
    hideJoystick();
}

-(void)beginAutoSave
{
    [NSTimer scheduledTimerWithTimeInterval:60 target:self selector:@selector(autoSave) userInfo:nil repeats:YES];
}

-(void)autoSave
{
    extern BOOL g_hasInGame;
    if (g_hasInGame) {
        PAL_SaveGame("9.rpg", 0);
    }
}

-(void)showSearchButton
{
    if (!btnSearch) {
        return;
    }
    if (btnSearch.hidden == YES) {
        btnSearch.hidden = NO;
    }
}

-(void)hideSearchButton
{
    if (!btnSearch) {
        return;
    }

    if (btnSearch.hidden == NO) {
        btnSearch.hidden = YES;
    }
}

-(void)showBackButton
{
    if (btnBack == nil) {
        SDL_Window* window = SDL_GetWindowFromID(g_windowId);
        if (!window) {
            return;
        }
        
        SDL_WindowData* windowData = (SDL_WindowData*)window->driverdata;
        UIView* mainView = windowData->viewcontroller.view;
        
        btnBack = [[UIButton alloc]initWithFrame:CGRectMake(425, 5, 50, 50)];
        [btnBack setImage:[UIImage imageNamed:@"back1"] forState:UIControlStateNormal];
        [btnBack setImage:[UIImage imageNamed:@"back"] forState:UIControlStateHighlighted];
        [btnBack addTarget:self action:@selector(onClickBack) forControlEvents:UIControlEventTouchUpInside];
        [mainView addSubview:btnBack];
    }
    
    if (btnBack.hidden == YES) {
        btnBack.hidden = NO;
    }
}

-(void)hideBackButton
{
    if (!btnBack) {
        return;
    }
    
    if (btnBack.hidden == NO) {
        btnBack.hidden = YES;
    }
}

-(void)onClickBack
{
    g_InputState.dwKeyPress |= kKeyMenu;
}

-(void)showJoystick
{
    if (textView.superview != nil) {
        return;
    }

    if (joystickBase == nil) {
        joystickBase = [[CGJoystick alloc]initWithFrame:CGRectMake(10, 160, 150, 150)];

        SDL_Window* window = SDL_GetWindowFromID(g_windowId);
        if (!window) {
            return;
        }
        
        SDL_WindowData* windowData = (SDL_WindowData*)window->driverdata;
        UIView* mainView = windowData->viewcontroller.view;
        [mainView insertSubview:joystickBase aboveSubview:btnMenu];
    }
    
    if (joystickBase.hidden == YES) {
        joystickBase.hidden = NO;
    }

    g_joystickType = JOYSTICK_MOVE;
}

-(void)hideJoystick
{
    if (joystickBase == nil) {
        return;
    }
    
    joystickBase.hidden = YES;
    g_joystickType = JOYSTICK_NONE;
}



-(void)onClickHelp
{
    SDL_Window* window = SDL_GetWindowFromID(g_windowId);
    if (!window) {
        return;
    }
    
    SDL_WindowData* windowData = (SDL_WindowData*)window->driverdata;
    UIView* mainView = windowData->viewcontroller.view;

    if (textView == nil) {
        textView = [[UITextView alloc]initWithFrame:CGRectMake(180, 50, 300, 270)];
        NSString* text = [NSString stringWithContentsOfFile:@"faq.txt" encoding:NSUTF8StringEncoding error:nil];
        if (text) {
            textView.text = text;
            textView.editable = NO;
            textView.alpha = 0.8;
        }
        
        systemView = [[SystemView alloc]initWithFrame:CGRectMake(0, 50, 180, 270)];
        [mainView addSubview:systemView];
        
#ifndef APP_FOR_APPSTORE
        _banner = [[DianJinOfferBanner alloc] initWithOfferBanner:CGPointMake(50, 0) style:kDJBannerStyle320_50];
        DianJinTransitionParam *transitionParam = [[DianJinTransitionParam alloc] init];
        transitionParam.animationType = kDJTransitionCube;
        transitionParam.animationSubType = kDJTransitionFromTop;
        transitionParam.duration = 1.0;
        [_banner setupTransition:transitionParam];
        [transitionParam release];
//        [_banner startWithTimeInterval:20 delegate:self];
        [mainView addSubview:_banner];
#endif
        
        moreApp = [UIButton buttonWithType:UIButtonTypeRoundedRect];
        moreApp.frame = CGRectMake(420, 12, 60, 40);
        moreApp.alpha = 0.8;
        [moreApp setTitle:@"攻略" forState:UIControlStateNormal];
        [moreApp setTitle:@"攻略" forState:UIControlStateHighlighted];
        //        [moreApp setImage:[UIImage imageNamed:@"more_app_normal"] forState:UIControlStateNormal];
        //        [moreApp setImage:[UIImage imageNamed:@"more_app_click"] forState:UIControlStateHighlighted];
        [moreApp addTarget:self action:@selector(onClickMoreApp) forControlEvents:UIControlEventTouchUpInside];
        [mainView addSubview:moreApp];

        self.isFAQ = YES;
        
    }
    
    if (textView.superview == nil) {
        [mainView addSubview:textView];
    } else {
        [textView removeFromSuperview];
    }
    
    BOOL isHiden = (textView.superview == nil);
    systemView.hidden = isHiden;
    
#ifndef APP_FOR_APPSTORE
    _banner.hidden = isHiden;
#endif
    moreApp.hidden = isHiden;
    
    if (isHiden) {
#ifndef APP_FOR_APPSTORE
        [_banner stop];
#endif
    } else {
#ifndef APP_FOR_APPSTORE
        [_banner startWithTimeInterval:20 delegate:self];
#endif
        hideJoystick();
    }
}

-(void)onClickMoreApp
{
#ifndef APP_FOR_APPSTORE
//    [[DianJinOfferPlatform defaultPlatform] presentOfferWall:self];
#endif
    isFAQ = !isFAQ;
    if (isFAQ) {
        NSString* text = [NSString stringWithContentsOfFile:@"faq.txt" encoding:NSUTF8StringEncoding error:nil];
        if (text) {
            textView.text = text;
            [textView setContentOffset:CGPointMake(0, 0) animated:NO];
        }
        
        [moreApp setTitle:@"攻略" forState:UIControlStateNormal];
        [moreApp setTitle:@"攻略" forState:UIControlStateHighlighted];
    } else {
        NSString* text = [NSString stringWithContentsOfFile:@"gl.txt" encoding:NSUTF8StringEncoding error:nil];
        if (text) {
            textView.text = text;
            [textView setContentOffset:CGPointMake(0, 0) animated:NO];
        }
        
        [moreApp setTitle:@"帮助" forState:UIControlStateNormal];
        [moreApp setTitle:@"帮助" forState:UIControlStateHighlighted];
    }
}

- (void)appActivatedDidFinish:(NSDictionary *)resultDic
{
//    NSLog(@"appActivatedDidFinish: %@", resultDic);
#ifndef APP_FOR_APPSTORE
    [[DianJinOfferPlatform defaultPlatform] getBalance:systemView];
#endif
}

-(void)onClickMenu
{
    extern BOOL g_showSystemMenu;
    if (g_showSystemMenu) {
        showJoystick();
        g_InputState.dwKeyPress |= kKeyMenu;
    } else {
        hideJoystick();
        g_InputState.dwKeyPress |= kKeyMainMenu;
    }
}

-(void)onClickSearch
{
    g_InputState.dwKeyPress |= kKeySearch;
}

- (NSString *)adMoGoApplicationKey {
	return @"3f0b839ef319410e993198c0fe4a772d"; //测试用ID
    //此字符串为您的App在芒果上的唯一标识
}

- (UIViewController *)viewControllerForPresentingModalView {
    SDL_Window* window = SDL_GetWindowFromID(g_windowId);
    if (!window) {
        return nil;
    }
    
    SDL_WindowData* windowData = (SDL_WindowData*)window->driverdata;
    return windowData->viewcontroller;
}

-(void)initAds
{
    adView = [AdMoGoView requestAdMoGoViewWithDelegate:self AndAdType:AdViewTypeNormalBanner
                                                ExpressMode:NO];
    [adView setFrame:CGRectZero];

    SDL_Window* window = SDL_GetWindowFromID(g_windowId);
    if (!window) {
        return;
    }
    
    SDL_WindowData* windowData = (SDL_WindowData*)window->driverdata;
    [windowData->viewcontroller.view addSubview:adView];
}

-(void)showAds
{
    if (adView == nil) {
        [self initAds];
    }
    
    if (adView.hidden == YES) {
        adView.hidden = NO;
        [adView resumeAdRequest];
    }
}

-(void)closeAds
{
    if (adView == nil) {
        return;
    }
    adView.hidden = YES;
    [adView pauseAdRequest];
    [adView removeFromSuperview];
    adView = nil;
}

- (void)adjustAdSize {	
	[UIView beginAnimations:@"AdResize" context:nil];
	[UIView setAnimationDuration:0.7];
	CGSize adSize = [adView actualAdSize];
	CGRect newFrame = adView.frame;
	newFrame.size.height = adSize.height;
	newFrame.size.width = adSize.width;
    int width, height;
    getScreenSize(&width, &height);
	newFrame.origin.x = (width - adSize.width)/2 - 20;
    newFrame.origin.y = 0;
	adView.frame = newFrame;
    
	[UIView commitAnimations];
} 


- (void)adMoGoDidReceiveAd:(AdMoGoView *)adMoGoView {
	//广告成功展示时调用
    [self adjustAdSize];
}

+(MyDelegate*)sharedInstance
{
    if (g_delegate == nil) {
        g_delegate = [[MyDelegate alloc]init];
    }   
    
    return g_delegate;
}
@end

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

void initButton()
{
    SDL_Window* window = SDL_GetWindowFromID(g_windowId);
    if (!window) {
        return;
    }
    
    SDL_WindowData* windowData = (SDL_WindowData*)window->driverdata;
    UIView* mainView = windowData->viewcontroller.view;
    
    UIButton* button = [UIButton buttonWithType:UIButtonTypeInfoLight];
    [button addTarget:[MyDelegate sharedInstance]  action:@selector(onClickHelp) forControlEvents:UIControlEventTouchUpInside];
    button.alpha = 0.4;
    
    [mainView addSubview:button];
    
    [MyDelegate sharedInstance].helpBtn = button;
    
//    [MobClick setLogEnabled:YES];
    [MobClick startWithAppkey:@"50045626527015611900001a"];
    
#ifndef APP_FOR_APPSTORE
    // Override point for customization after application launch.
	[[DianJinOfferPlatform defaultPlatform] setAppId:7209 andSetAppKey:@"13891e5c79ce10b018d2d5a7c44dabd4"];
	[[DianJinOfferPlatform defaultPlatform] setOfferViewColor:kDJBlueColor];
    [[DianJinOfferPlatform defaultPlatform] setOfferViewAutoRotate:YES];
#endif
    
    showAds();
    
    [[MyDelegate sharedInstance]beginAutoSave];

    NSUserDefaults* defaults = [NSUserDefaults standardUserDefaults];
    if (defaults) {
        if ([defaults boolForKey:@"Tip"] == NO) {
            [defaults setBool:YES forKey:@"Tip"];
            
            UIAlertView* alert = [[UIAlertView alloc]initWithTitle:@"提示" message:@"点击左上角的按钮可以查看触屏操作方式和游戏攻略" delegate:nil cancelButtonTitle:@"知道了" otherButtonTitles:nil,nil];
            [alert show];
        }
        
        int mode = [defaults integerForKey:@"BattleMode"];
        g_isClassicMode = (mode == 0 || mode == 1);
        
        int joystick = [defaults integerForKey:@"JoystickMode"];
        g_useJoyStick = (joystick == 0 || joystick == 1);
    }
}

void hideButton()
{
    UIButton* btn = [MyDelegate sharedInstance].helpBtn;
    if (btn) {
        [btn removeFromSuperview];
    }
}

void showMenu()
{
    [[MyDelegate sharedInstance] showMenuBtn];
}

void hideMenu()
{
    [[MyDelegate sharedInstance] hideMenuBtn];
}

void showSearchButton()
{
    [[MyDelegate sharedInstance] showSearchButton];
}

void hideSearchButton()
{
    [[MyDelegate sharedInstance]hideSearchButton];
}

void showAds()
{
    [[MyDelegate sharedInstance]showAds];
}

void closeAds()
{
    [[MyDelegate sharedInstance]closeAds];
}

void beginAutoSave()
{
    [[MyDelegate sharedInstance]beginAutoSave];
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

    if (g_joystickType == JOYSTICK_NONE) {
        [[MyDelegate sharedInstance]showJoystick];
    }
}

void hideJoystick()
{
    if (g_joystickType == JOYSTICK_NONE) {
        return;
    }

    [[MyDelegate sharedInstance]hideJoystick];
}

void showBackButton()
{
    [[MyDelegate sharedInstance]showBackButton];
}

void hideBackButton()
{
    [[MyDelegate sharedInstance]hideBackButton];
}

#endif