//
//  iOSUtil.m
//  Pal_iOS
//
//  Created by 王 佳 on 12-7-16.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
#if 1
#import <Foundation/Foundation.h>
#import "iOSUtil.h"
#include "main.h"

#import "video/uikit/SDL_uikitwindow.h"
#import "AdMoGoView.h"
//#import "MobClick.h"

@interface MyDelegate : NSObject<AdMoGoDelegate>
{
    UIButton* helpBtn;
    UITextView* textView;
    
    AdMoGoView *adView;
}
@property(retain, nonatomic) UIButton* helpBtn;

+(MyDelegate*)sharedInstance;
-(void)onClickHelp;

-(void)initAds;
-(void)showAds;
-(void)closeAds;
@end

MyDelegate* g_delegate = nil;

@implementation MyDelegate
@synthesize helpBtn;
-(void)onClickHelp
{
    if (textView == nil) {
        textView = [[UITextView alloc]initWithFrame:CGRectMake(80, 0, 300, 320)];
        NSString* text = [NSString stringWithContentsOfFile:@"gl.txt" encoding:NSUTF8StringEncoding error:nil];
        if (text) {
            textView.text = text;
            textView.editable = NO;
            textView.alpha = 0.8;
        }
    }
    
    if (textView.superview == nil) {
        SDL_Window* window = SDL_GetWindowFromID(g_windowId);
        if (!window) {
            return;
        }
        
        SDL_WindowData* windowData = (SDL_WindowData*)window->driverdata;
        UIView* mainView = windowData->viewcontroller.view;
        [mainView addSubview:textView];
    } else {
        [textView removeFromSuperview];
    }
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

    adView.hidden = NO;
}

-(void)closeAds
{
    if (adView == nil) {
        return;
    }
    adView.hidden = YES;
    [adView pauseAdRequest];
    [adView removeFromSuperview];
    adView.delegate = nil;
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
//    [MobClick startWithAppkey:@"50045626527015611900001a"];
    
    showAds();
}

void hideButton()
{
    UIButton* btn = [MyDelegate sharedInstance].helpBtn;
    if (btn) {
        [btn removeFromSuperview];
    }
}

void showAds()
{
    [[MyDelegate sharedInstance]showAds];
}

void closeAds()
{
    [[MyDelegate sharedInstance]closeAds];
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
#endif