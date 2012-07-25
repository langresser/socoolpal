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

extern BOOL g_isClassicMode;
extern BOOL g_useJoyStick;

@implementation SystemView
- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {      
        UIImageView* bgImage = [[UIImageView alloc]initWithImage:[UIImage imageNamed:@"bg2"]];
        bgImage.frame = CGRectMake(0, 0, frame.size.width, frame.size.height);
        [self addSubview:bgImage];
        
        UILabel* modeLabel = [[UILabel alloc]initWithFrame:CGRectMake(10, 50, 70, 24)];
        modeLabel.text = @"战斗模式:";
        modeLabel.font = [UIFont systemFontOfSize:15];
        modeLabel.backgroundColor = [UIColor clearColor];
        [self addSubview:modeLabel];
        
        switchMode = [UIButton buttonWithType:UIButtonTypeRoundedRect];
        switchMode.frame = CGRectMake(80, 50, 70, 24);
        
        [switchMode setTitle:(g_isClassicMode ? @"回合制" : @"即时制") forState:UIControlStateNormal];
        [switchMode setTitle:(g_isClassicMode ? @"回合制" : @"即时制") forState:UIControlStateHighlighted];
        [switchMode addTarget:self  action:@selector(onClickMode) forControlEvents:UIControlEventTouchUpInside];
        switchMode.alpha = 0.8;
        [self addSubview:switchMode];
        
        UILabel* joystickLabel = [[UILabel alloc]initWithFrame:CGRectMake(10, 80, 70, 24)];
        joystickLabel.text = @"显示摇杆:";
        joystickLabel.backgroundColor = [UIColor clearColor];
        joystickLabel.font = [UIFont systemFontOfSize:15];
        [self addSubview:joystickLabel];
        
        UISwitch* joystickBtn = [[UISwitch alloc]initWithFrame:CGRectMake(80, 80, 40, 20)];
        joystickBtn.on = g_useJoyStick ? YES : NO;
        
        [joystickBtn addTarget:self  action:@selector(onClickJoystick) forControlEvents:UIControlEventTouchUpInside];
        joystickBtn.alpha = 0.8;
        [self addSubview:joystickBtn];
        
        UIButton* feedBack = [UIButton buttonWithType:UIButtonTypeRoundedRect];
        feedBack.frame = CGRectMake(10, 110, 70, 24);
        [feedBack setTitle:@"bug反馈" forState:UIControlStateNormal];
        [feedBack setTitle:@"bug反馈" forState:UIControlStateHighlighted];
        feedBack.alpha = 0.8;
        [feedBack addTarget:self  action:@selector(onClickFeedBack) forControlEvents:UIControlEventTouchUpInside];
        [self addSubview:feedBack];
        
        UIButton* btnBBS = [UIButton buttonWithType:UIButtonTypeRoundedRect];
        btnBBS.frame = CGRectMake(10, 140, 70, 24);
        [btnBBS setTitle:@"论坛交流" forState:UIControlStateNormal];
        [btnBBS setTitle:@"论坛交流" forState:UIControlStateHighlighted];
        btnBBS.alpha = 0.8;
        [btnBBS addTarget:self  action:@selector(onClickBBS) forControlEvents:UIControlEventTouchUpInside];
        [self addSubview:btnBBS];
        
        
//        UILabel* hackLabel = [[UILabel alloc]initWithFrame:CGRectMake(10, 180, 120, 24)];
//        hackLabel.text = @"金手指功能:";
//        hackLabel.backgroundColor = [UIColor clearColor];
//        hackLabel.font = [UIFont systemFontOfSize:15];
//        [self addSubview:hackLabel];
//        
//        UILabel* moveLabel = [[UILabel alloc]initWithFrame:CGRectMake(10, 210, 70, 24)];
//        moveLabel.text = @"移动模式:";
//        moveLabel.font = [UIFont systemFontOfSize:15];
//        moveLabel.backgroundColor = [UIColor clearColor];
//        [self addSubview:moveLabel];
//        
//        moveButton = [UIButton buttonWithType:UIButtonTypeRoundedRect];
//        moveButton.frame = CGRectMake(80, 210, 70, 24);
//        
//        [moveButton setTitle:(isFlyMode() ? @"穿墙" : @"正常") forState:UIControlStateNormal];
//        [moveButton setTitle:(isFlyMode() ? @"穿墙" : @"正常") forState:UIControlStateHighlighted];
//        [moveButton addTarget:self  action:@selector(onClickMove) forControlEvents:UIControlEventTouchUpInside];
//        moveButton.alpha = 0.8;
//        [self addSubview:moveButton];
//        
//        UIButton* uplevBtn = [UIButton buttonWithType:UIButtonTypeRoundedRect];
//        uplevBtn.frame = CGRectMake(10, 240, 100, 24);
//        [uplevBtn setTitle:@"全角色升级" forState:UIControlStateNormal];
//        [uplevBtn setTitle:@"全角色升级" forState:UIControlStateHighlighted];
//        uplevBtn.alpha = 0.8;
//        [uplevBtn addTarget:self  action:@selector(onClickLevelUp) forControlEvents:UIControlEventTouchUpInside];
//        [self addSubview:uplevBtn];
//        
//        UIButton* addMoneyBtn = [UIButton buttonWithType:UIButtonTypeRoundedRect];
//        addMoneyBtn.frame = CGRectMake(10, 270, 100, 24);
//        [addMoneyBtn setTitle:@"加5000金钱" forState:UIControlStateNormal];
//        [addMoneyBtn setTitle:@"加5000金钱" forState:UIControlStateHighlighted];
//        addMoneyBtn.alpha = 0.8;
//        [addMoneyBtn addTarget:self  action:@selector(onClickAddMoney) forControlEvents:UIControlEventTouchUpInside];
//        [self addSubview:addMoneyBtn];
    }
    return self;
}

-(void)onClickMove
{
}

-(void)onClickLevelUp
{
}

-(void)onClickAddMoney
{
    
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
