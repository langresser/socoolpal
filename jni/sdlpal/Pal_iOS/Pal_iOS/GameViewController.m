//
//  GameViewController.m
//  SDLJY_iOS
//
//  Created by 佳 王 on 12-11-25.
//  Copyright (c) 2012年 佳 王. All rights reserved.
//

#import "GameViewController.h"
#import "util.h"

extern int g_pressButton;

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
        int joystick = [defaults integerForKey:@"JoystickMode"];
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
    
    btnA = [UIButton buttonWithType:UIButtonTypeCustom];
    btnA.frame = rectA;
    [btnA setImage:[UIImage imageNamed:@"anormal.png"] forState:UIControlStateNormal];
    [btnA setImage:[UIImage imageNamed:@"aclick.png"] forState:UIControlStateHighlighted];
    [btnA addTarget:self action:@selector(onClickA) forControlEvents:UIControlEventTouchUpInside];
    
    btnB = [UIButton buttonWithType:UIButtonTypeCustom];
    btnB.frame = rectB;
    [btnB setImage:[UIImage imageNamed:@"bnormal.png"] forState:UIControlStateNormal];
    [btnB setImage:[UIImage imageNamed:@"bclick.png"] forState:UIControlStateHighlighted];
    [btnB addTarget:self action:@selector(onClickB) forControlEvents:UIControlEventTouchUpInside];

    joystick.alpha = 0.3;
    btnMenu.alpha = 0.3;
    btnA.alpha = 0.3;
    btnB.alpha = 0.3;

    [self.view addSubview:btnMenu];
    [self.view addSubview:joystick];
    [self.view addSubview:btnA];
    [self.view addSubview:btnB];
    
    
    
    SDL_WindowData* windowData = (SDL_WindowData*)window->driverdata;
    UIView* mainView = windowData->viewcontroller.view;
    
    UIButton* button = [UIButton buttonWithType:UIButtonTypeInfoLight];
    [button addTarget:[MyDelegate sharedInstance]  action:@selector(onClickHelp) forControlEvents:UIControlEventTouchUpInside];
    button.alpha = 0.4;
    
    [mainView addSubview:button];
    
    [MyDelegate sharedInstance].helpBtn = button;
    
    //    [MobClick setLogEnabled:YES];
    [MobClick startWithAppkey:@"50045626527015611900001a"];
    
    [UMFeedback checkWithAppkey:@"50045626527015611900001a"];
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
    
    if (btnMenu == nil) {
        btnMenu = [UIButton buttonWithType:UIButtonTypeCustom];
        
        if (isPad()) {
            btnMenu.frame = CGRectMake(920, 710, 50, 50);
        } else {
            btnMenu.frame = CGRectMake(400, 280, 40, 40);
        }
        
        [btnMenu setImage:[UIImage imageNamed:@"back1"] forState:UIControlStateNormal];
        [btnMenu setImage:[UIImage imageNamed:@"back"] forState:UIControlStateHighlighted];
        btnMenu.alpha = 0.5;
        [btnMenu addTarget:self action:@selector(onClickMenu) forControlEvents:UIControlEventTouchUpInside];
        
        SDL_Window* window = SDL_GetWindowFromID(g_windowId);
        if (!window) {
            return;
        }
        
        SDL_WindowData* windowData = (SDL_WindowData*)window->driverdata;
        UIView* mainView = windowData->viewcontroller.view;
        [mainView addSubview:btnMenu];
        
        if (isPad()) {
            btnSearch = [[UIButton alloc]initWithFrame:CGRectMake(970, 640, 50, 50)];
        } else {
            btnSearch = [[UIButton alloc]initWithFrame:CGRectMake(440, 230, 40, 40)];
        }
        
        [btnSearch setImage:[UIImage imageNamed:@"search"] forState:UIControlStateNormal];
        [btnSearch setImage:[UIImage imageNamed:@"search2"] forState:UIControlStateHighlighted];
        btnSearch.alpha = 0.8;
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

-(void)onClickA
{
    g_pressButton = 1;
}

-(void)onClickB
{
    g_pressButton = 2;
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
    if (textView.superview != nil) {
        return;
    }
    
    if (joystickBase == nil) {
        int width, height;
        getScreenSize(&width, &height);
        
        if (isPad()) {
            joystickBase = [[CGJoystick alloc]initWithFrame:CGRectMake(10, height - 200 - 5, 200, 200)];
        } else {
            joystickBase = [[CGJoystick alloc]initWithFrame:CGRectMake(5, 185, 130, 130)];
        }
        
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


@end
