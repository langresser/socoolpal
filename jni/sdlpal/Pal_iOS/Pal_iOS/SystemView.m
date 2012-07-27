//
//  SystemView.m
//  Pal_iOS
//
//  Created by 王 佳 on 12-7-26.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "SystemView.h"
#import <QuartzCore/QuartzCore.h>
#import "InAppPurchaseMgr.h"
#import "MobClick.h"
#import "UMFeedback.h"
#import "video/uikit/SDL_uikitwindow.h"
#include "SDL_compat.h"
#include "input.h"
#include "util.h"
#include "hack.h"
#import "UIDevice+Util.h"

#ifdef APP_FOR_APPSTORE
#import "InAppPurchaseMgr.h"
#else
#import <DianJinOfferPlatform/DianJinOfferPlatform.h>
#import <DianJinOfferPlatform/DianJinOfferBanner.h>
#import <DianJinOfferPlatform/DianJinBannerSubViewProperty.h>
#import <DianJinOfferPlatform/DianJinTransitionParam.h>
#endif

extern BOOL g_isClassicMode;
extern BOOL g_useJoyStick;
int g_currentMB = 0;

@implementation SystemView
- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {      
        UIImageView* bgImage = [[UIImageView alloc]initWithImage:[UIImage imageNamed:@"bg2"]];
        bgImage.frame = CGRectMake(0, 0, frame.size.width, frame.size.height);
        [self addSubview:bgImage];
        
        UILabel* modeLabel = [[UILabel alloc]initWithFrame:CGRectMake(10, 30, 70, 24)];
        modeLabel.text = @"战斗模式:";
        modeLabel.font = [UIFont systemFontOfSize:15];
        modeLabel.backgroundColor = [UIColor clearColor];
        [self addSubview:modeLabel];
        
        switchMode = [UIButton buttonWithType:UIButtonTypeRoundedRect];
        switchMode.frame = CGRectMake(80, 30, 70, 24);
        
        [switchMode setTitle:(g_isClassicMode ? @"回合制" : @"即时制") forState:UIControlStateNormal];
        [switchMode setTitle:(g_isClassicMode ? @"回合制" : @"即时制") forState:UIControlStateHighlighted];
        [switchMode addTarget:self  action:@selector(onClickMode) forControlEvents:UIControlEventTouchUpInside];
        switchMode.alpha = 0.8;
        [self addSubview:switchMode];
        
        UILabel* joystickLabel = [[UILabel alloc]initWithFrame:CGRectMake(10, 62, 70, 24)];
        joystickLabel.text = @"显示摇杆:";
        joystickLabel.backgroundColor = [UIColor clearColor];
        joystickLabel.font = [UIFont systemFontOfSize:15];
        [self addSubview:joystickLabel];
        
        UISwitch* joystickBtn = [[UISwitch alloc]initWithFrame:CGRectMake(80, 65, 40, 20)];
        joystickBtn.on = g_useJoyStick ? YES : NO;
        
        [joystickBtn addTarget:self  action:@selector(onClickJoystick) forControlEvents:UIControlEventTouchUpInside];
        joystickBtn.alpha = 0.8;
        [self addSubview:joystickBtn];
        
        UIButton* feedBack = [UIButton buttonWithType:UIButtonTypeRoundedRect];
        feedBack.frame = CGRectMake(10, 95, 70, 24);
        [feedBack setTitle:@"bug反馈" forState:UIControlStateNormal];
        [feedBack setTitle:@"bug反馈" forState:UIControlStateHighlighted];
        feedBack.alpha = 0.8;
        [feedBack addTarget:self  action:@selector(onClickFeedBack) forControlEvents:UIControlEventTouchUpInside];
        [self addSubview:feedBack];
        
        UIButton* btnBBS = [UIButton buttonWithType:UIButtonTypeRoundedRect];
        btnBBS.frame = CGRectMake(90, 95, 70, 24);
        [btnBBS setTitle:@"论坛交流" forState:UIControlStateNormal];
        [btnBBS setTitle:@"论坛交流" forState:UIControlStateHighlighted];
        btnBBS.alpha = 0.8;
        [btnBBS addTarget:self  action:@selector(onClickBBS) forControlEvents:UIControlEventTouchUpInside];
        [self addSubview:btnBBS];
        
        hackLabel = [[UILabel alloc]initWithFrame:CGRectMake(10, 130, 150, 24)];
        hackLabel.text = [self testHackEnable] ? @"金手指功能:(已开启)" : @"金手指功能:(未开启)";
        hackLabel.backgroundColor = [UIColor clearColor];
        hackLabel.font = [UIFont systemFontOfSize:15];
        [self addSubview:hackLabel];
        
        UILabel* moveLabel = [[UILabel alloc]initWithFrame:CGRectMake(10, 160, 70, 24)];
        moveLabel.text = @"移动模式:";
        moveLabel.font = [UIFont systemFontOfSize:15];
        moveLabel.backgroundColor = [UIColor clearColor];
        [self addSubview:moveLabel];
        
        moveButton = [UIButton buttonWithType:UIButtonTypeRoundedRect];
        moveButton.frame = CGRectMake(80, 160, 70, 24);
        
        [moveButton setTitle:(isFlyMode() ? @"穿墙" : @"正常") forState:UIControlStateNormal];
        [moveButton setTitle:(isFlyMode() ? @"穿墙" : @"正常") forState:UIControlStateHighlighted];
        [moveButton addTarget:self  action:@selector(onClickMove) forControlEvents:UIControlEventTouchUpInside];
        moveButton.alpha = 0.8;
        [self addSubview:moveButton];
        
        UIButton* uplevBtn = [UIButton buttonWithType:UIButtonTypeRoundedRect];
        uplevBtn.frame = CGRectMake(10, 190, 100, 24);
        [uplevBtn setTitle:@"全角色升级" forState:UIControlStateNormal];
        [uplevBtn setTitle:@"全角色升级" forState:UIControlStateHighlighted];
        uplevBtn.alpha = 0.8;
        [uplevBtn addTarget:self  action:@selector(onClickLevelUp) forControlEvents:UIControlEventTouchUpInside];
        [self addSubview:uplevBtn];
        
        UIButton* addMoneyBtn = [UIButton buttonWithType:UIButtonTypeRoundedRect];
        addMoneyBtn.frame = CGRectMake(10, 220, 100, 24);
        [addMoneyBtn setTitle:@"加5000金钱" forState:UIControlStateNormal];
        [addMoneyBtn setTitle:@"加5000金钱" forState:UIControlStateHighlighted];
        addMoneyBtn.alpha = 0.8;
        [addMoneyBtn addTarget:self  action:@selector(onClickAddMoney) forControlEvents:UIControlEventTouchUpInside];
        [self addSubview:addMoneyBtn];
        
#ifdef APP_FOR_APPSTORE
        [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(onPurchaseOk) name:kIAPSucceededNotification object:nil];
        [[InAppPurchaseMgr sharedInstance]loadStore];
#endif
    }
    return self;
}

-(void)onClickMove
{
    if ([self isHackEnable]) {
        setFlyMode(!isFlyMode());

        [moveButton setTitle:(isFlyMode() ? @"穿墙" : @"正常") forState:UIControlStateNormal];
        [moveButton setTitle:(isFlyMode() ? @"穿墙" : @"正常") forState:UIControlStateHighlighted];
    }
}

-(void)onClickLevelUp
{
    if ([self isHackEnable]) {
        uplevel();
    }
}

-(void)onClickAddMoney
{
    if ([self isHackEnable]) {
        addMoney();
    }
}

-(BOOL)testHackEnable
{
    NSString* flag = [[NSUserDefaults standardUserDefaults] stringForKey:kRemoveAdsFlag];
    if (flag && [flag isEqualToString:[[UIDevice currentDevice] uniqueDeviceIdentifier]]) {
        return YES;
    }
    
    return NO;
}

-(void)onPurchaseOk
{
    hackLabel.text = @"金手指功能:(已开启)";
}

-(BOOL)isHackEnable
{
//    [[NSUserDefaults standardUserDefaults] removeObjectForKey:kRemoveAdsFlag];
//    [[NSUserDefaults standardUserDefaults] synchronize];
    NSString* flag = [[NSUserDefaults standardUserDefaults] stringForKey:kRemoveAdsFlag];
    if (flag && [flag isEqualToString:[[UIDevice currentDevice] uniqueDeviceIdentifier]]) {
        return YES;
    }

#ifdef APP_FOR_APPSTORE
    [[InAppPurchaseMgr sharedInstance]purchaseProUpgrade];
#else
    [[DianJinOfferPlatform defaultPlatform] getBalance:self];

    UIAlertView* alert = [[UIAlertView alloc]initWithTitle:@"提示" message:@"当您获得100元宝时将自动开启金手指功能。您可以通过安装精品推荐应用的方式免费获取元宝。" delegate:nil cancelButtonTitle:@"知道了" otherButtonTitles:nil, nil];
    [alert show];
#endif
    return NO;
}

- (void)getBalanceDidFinish:(NSDictionary *)dict
{
    NSNumber *result = [dict objectForKey: @"result"]; 
    int ret = [result intValue];
    
    if (ret == 0) {
        NSNumber *balance = [dict objectForKey:@"balance"];
        g_currentMB = [balance floatValue];
        
        if (g_currentMB >= 100) {
            NSUserDefaults* defaults = [NSUserDefaults standardUserDefaults];
            if (defaults) {
                hackLabel.text = @"金手指功能:(已开启)";
                [[NSUserDefaults standardUserDefaults] setObject:[[UIDevice currentDevice] uniqueDeviceIdentifier] forKey:kRemoveAdsFlag];
                [[NSUserDefaults standardUserDefaults] synchronize];
            }
        }
    }
}

-(void)onClickMode
{
    g_isClassicMode = !g_isClassicMode;
    NSUserDefaults* defaults = [NSUserDefaults standardUserDefaults];
    if (defaults) {
        [defaults setInteger:(g_isClassicMode ? 1 : 2) forKey:@"BattleMode"];
    }
    
    [switchMode setTitle:(g_isClassicMode ? @"回合制" : @"即时制") forState:UIControlStateNormal];
    [switchMode setTitle:(g_isClassicMode ? @"回合制" : @"即时制") forState:UIControlStateHighlighted];
}

-(void)onClickJoystick
{
    g_useJoyStick = !g_useJoyStick;
    
    NSUserDefaults* defaults = [NSUserDefaults standardUserDefaults];
    if (defaults) {
        [defaults setInteger:(g_useJoyStick ? 1 : 2) forKey:@"JoystickMode"];
    }
    
    if (g_useJoyStick) {
        showJoystick();
    } else {
        hideJoystick();
    }
}



-(void)onClickFeedBack
{
    SDL_Window* window = SDL_GetWindowFromID(g_windowId);
    if (!window) {
        return;
    }
    
    SDL_WindowData* windowData = (SDL_WindowData*)window->driverdata;
    
    [UMFeedback showFeedback:windowData->viewcontroller withAppkey:@"50045626527015611900001a"];
}

-(void)onClickBBS
{
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"http://bananastudio.cn/bbs/forum.php"]]; 
}
@end
