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
#import "AdViewDelegateProtocol.h"
#import "AdViewView.h"

@interface MyDelegate : NSObject<AdViewDelegate>
{
    UIButton* helpBtn;
    UITextView* textView;
    
    AdViewView *adView;
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

- (UIViewController *)viewControllerForPresentingModalView {
    SDL_Window* window = SDL_GetWindowFromID(g_windowId);
    if (!window) {
        return nil;
    }
    
    SDL_WindowData* windowData = (SDL_WindowData*)window->driverdata;
    return windowData->viewcontroller;
}

- (NSString *)adViewApplicationKey {
    return @"SDK20122315110722t9kwandrzfnrr1i";
}


-(void)initAds
{
    adView = [AdViewView requestAdViewViewWithDelegate:self];
	adView.autoresizingMask =
    UIViewAutoresizingFlexibleLeftMargin|UIViewAutoresizingFlexibleRightMargin;	

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
}

- (BOOL)adGpsMode {
    return NO;
}

-(AdviewBannerSize)PreferBannerSize {
    return AdviewBannerSize_320x50; 
}

- (void)adjustAdSize {
	[UIView beginAnimations:@"AdResize" context:nil];
	[UIView setAnimationDuration:0.7];
	CGSize adSize = [adView actualAdSize];
	CGRect newFrame = adView.frame;
	newFrame.size.height = adSize.height;
	newFrame.size.width = adSize.width;
    CGRect rectMain = [UIScreen mainScreen].bounds;
    int width = rectMain.size.height > rectMain.size.width ? rectMain.size.height : rectMain.size.width;

	newFrame.origin.x = (width - adSize.width);
    //newFrame.origin.y = (self.view.bounds.size.height - adSize.height);
	adView.frame = newFrame;
	[UIView commitAnimations];
}

- (void)adViewDidReceiveAd:(AdViewView *)adViewView {
	[self adjustAdSize];
}

#warning modify when release
#ifdef DEBUG
- (BOOL)adViewTestMode {
	return YES;
}

- (BOOL)adViewLogMode {
    return YES;
}
#else
- (BOOL)adViewTestMode {
	return NO;
}

- (BOOL)adViewLogMode {
    return NO;
}
#endif

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