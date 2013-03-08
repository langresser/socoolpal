//
//  GameViewController.m
//  SDLJY_iOS
//
//  Created by 佳 王 on 12-11-25.
//  Copyright (c) 2012年 佳 王. All rights reserved.
//

#import "GameViewController.h"
#import "util.h"
#include "input.h"
#include "global.h"

extern BOOL g_isClassicMode;
extern int g_joystickType;
extern BOOL g_useJoyStick;
extern int g_currentMB;

#define JOYSTICK_NONE 0
#define JOYSTICK_MOVE 1
#define JOYSTICK_BATTLE 2

@implementation GameViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    NSUserDefaults* defaults = [NSUserDefaults standardUserDefaults];
    if (defaults) {
        g_currentMB = [defaults integerForKey:@"MB"];
        if ([defaults boolForKey:@"Tip"] == NO) {
            [defaults setBool:YES forKey:@"Tip"];
            
            UIAlertView* alert = [[UIAlertView alloc]initWithTitle:@"提示" message:@"点击左上角的按钮可以查看触屏操作方式和游戏攻略" delegate:nil cancelButtonTitle:@"知道了" otherButtonTitles:nil,nil];
            [alert show];
        }
        
        int mode = [defaults integerForKey:@"BattleMode"];
        g_isClassicMode = (mode == 0 || mode == 1);
        
        int joystick1 = [defaults integerForKey:@"JoystickMode"];
        g_useJoyStick = (joystick1 == 0 || joystick1 == 1);
    }
    
    int width, height;
    getScreenSize(&width, &height);
    CGRect rectA, rectB;
    
    if (isPad()) {
        joystick = [[CGJoystick alloc]initWithFrame:CGRectMake(20, height - 150 - 20, 150, 150)];
        rectA = CGRectMake(965, 710, 50, 50);
        rectB = CGRectMake(900, 710, 50, 50);
    } else {
        joystick = [[CGJoystick alloc]initWithFrame:CGRectMake(5, 200, 110, 110)];
        rectA = CGRectMake(430, 250, 50, 50);
        rectB = CGRectMake(370, 250, 50, 50);
    }
    
    btnMenu = [UIButton buttonWithType:UIButtonTypeCustom];
    btnMenu.frame = CGRectMake(width - 50, 0, 50, 50);
    [btnMenu setImage:[UIImage imageNamed:@"pause.png"] forState:UIControlStateNormal];
    [btnMenu addTarget:self action:@selector(onClickMenu) forControlEvents:UIControlEventTouchUpInside];

    joystick.alpha = 0.3;
    btnMenu.alpha = 0.3;

    [self.view addSubview:btnMenu];
    [self.view addSubview:joystick];
    
    btnGameMenu = [UIButton buttonWithType:UIButtonTypeCustom];
    
    if (isPad()) {
        btnGameMenu.frame = CGRectMake(920, 710, 50, 50);
    } else {
        btnGameMenu.frame = CGRectMake(400, 280, 40, 40);
    }
    
    [btnGameMenu setImage:[UIImage imageNamed:@"back1"] forState:UIControlStateNormal];
    [btnGameMenu setImage:[UIImage imageNamed:@"back"] forState:UIControlStateHighlighted];
    btnGameMenu.alpha = 0.5;
    [btnGameMenu addTarget:self action:@selector(onClickGameMenu) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:btnGameMenu];
    
    if (isPad()) {
        btnSearch = [[UIButton alloc]initWithFrame:CGRectMake(970, 640, 50, 50)];
    } else {
        btnSearch = [[UIButton alloc]initWithFrame:CGRectMake(440, 230, 40, 40)];
    }
    
    [btnSearch setImage:[UIImage imageNamed:@"search"] forState:UIControlStateNormal];
    [btnSearch setImage:[UIImage imageNamed:@"search2"] forState:UIControlStateHighlighted];
    btnSearch.alpha = 0.8;
    [btnSearch addTarget:self action:@selector(onClickSearch) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:btnSearch];
    
    if (isPad()) {
        btnBack = [[UIButton alloc]initWithFrame:CGRectMake(970, 5, 50, 50)];
    } else {
        btnBack = [[UIButton alloc]initWithFrame:CGRectMake(425, 5, 50, 50)];
    }
    [btnBack setImage:[UIImage imageNamed:@"back1"] forState:UIControlStateNormal];
    [btnBack setImage:[UIImage imageNamed:@"back"] forState:UIControlStateHighlighted];
    [btnBack addTarget:self action:@selector(onClickBack) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:btnBack];
    
    joystick.hidden = YES;
    btnBack.hidden = YES;
    btnSearch.hidden = YES;
    btnGameMenu.hidden = YES;
    

    [self beginAutoSave];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(appActivatedDidFinish:) name:kDJAppActivateDidFinish object:nil];
}


-(void)onClickGameMenu
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

- (void)appActivatedDidFinish:(NSNotification *)notice;
{
    NSDictionary* resultDic = [notice object];
    NSLog(@"%@", resultDic);
    NSNumber *result = [resultDic objectForKey:@"result"];
    if ([result boolValue]) {
        NSNumber *awardAmount = [resultDic objectForKey:@"awardAmount"];
        NSString *identifier = [resultDic objectForKey:@"identifier"];
        NSLog(@"app identifier = %@", identifier);
        g_currentMB += [awardAmount floatValue];
        [[NSUserDefaults standardUserDefaults]setInteger:g_currentMB forKey:@"MB"];
        [[NSUserDefaults standardUserDefaults]synchronize];
    }
}

-(void)showSettingPopup:(BOOL)show
{
    if (show) {
        if (isPad()) {
            if (popoverVC == nil) {
                settingVC = [[SettingViewController alloc]initWithNibName:nil bundle:nil];
                popoverVC = [[UIPopoverController alloc] initWithContentViewController:settingVC];
                popoverVC.delegate = self;
            }
            
            CGRect rect = CGRectMake(100, 60, 10, 10);
            [popoverVC presentPopoverFromRect:rect inView:self.view permittedArrowDirections:UIPopoverArrowDirectionLeft animated:YES];
        } else {
            if (settingVC == nil) {
                settingVC = [[SettingViewController alloc]initWithNibName:nil bundle:nil];
            }
            
            if ([[[UIDevice currentDevice]systemVersion]floatValue] >= 5.0) {
                [self presentViewController:settingVC animated:YES completion:nil];
            } else {
                [self presentModalViewController:settingVC animated:YES];
            }
        }
    } else {
        if (isPad()) {
            [popoverVC dismissPopoverAnimated:YES];
        } else {
            if ([[[UIDevice currentDevice]systemVersion]floatValue] >= 5.0) {
                [settingVC dismissViewControllerAnimated:YES completion:nil];
            } else {
                [settingVC dismissModalViewControllerAnimated:YES];
            }
        }
    }
}

-(void)onClickMenu
{
    [self showSettingPopup:YES];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(BOOL)shouldAutorotate
{
    return YES;
}

- (NSUInteger)supportedInterfaceOrientations
{
    return UIInterfaceOrientationMaskLandscape;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)orient
{
    return UIInterfaceOrientationIsLandscape(orient);
}

-(void)onClickBack
{
    g_InputState.dwKeyPress |= kKeyMenu;
}

-(void)showJoystick
{
    if (g_joystickType != JOYSTICK_NONE) {
        return;
    }
    
    if (joystick.hidden == YES) {
        joystick.hidden = NO;
    }
    
    g_joystickType = JOYSTICK_MOVE;
}

-(void)hideJoystick
{
    if (g_joystickType == JOYSTICK_NONE) {
        return;
    }

    if (joystick == nil) {
        return;
    }
    
    joystick.hidden = YES;
    g_joystickType = JOYSTICK_NONE;
}

-(void)showGameMenu
{
    btnGameMenu.hidden = NO;
}

-(void)hideGameMenu
{
    btnGameMenu.hidden = YES;
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
    if (!btnBack) {
        return;
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


@end
