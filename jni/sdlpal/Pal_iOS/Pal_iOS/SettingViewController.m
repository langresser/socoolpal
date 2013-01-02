//
//  SettingViewController.m
//  MD
//
//  Created by 王 佳 on 12-9-5.
//  Copyright (c) 2012年 Gingco.Net New Media GmbH. All rights reserved.
//

#import "SettingViewController.h"
#import <QuartzCore/QuartzCore.h>
#import "UIDevice+Util.h"
#import "UIGlossyButton.h"
#import "UIView+LayerEffects.h"
#import "UMFeedback.h"
#import "AppDelegate.h"
#import "InAppPurchaseMgr.h"
#import "GameViewController.h"

#define kPurchaseCanglong @"kPurchaseCanglong"
#define kPurchaseCangyan @"kPurchaseCangyan"

extern BOOL g_isClassicMode;
extern BOOL g_useJoyStick;
int g_currentMB = 0;
extern int g_app_type;

@implementation SettingViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

-(void)loadView
{
    settingView = [[UIView alloc]initWithFrame:CGRectMake(0, 0, 320, 480)];
    settingView.backgroundColor = [UIColor colorWithRed:240.0 / 255 green:248.0 / 255 blue:1.0 alpha:1.0];
    
    float offsetY = 0;
#ifndef APP_FOR_APPSTORE
    _banner = [[DianJinOfferBanner alloc] initWithOfferBanner:CGPointMake(0, 0) style:kDJBannerStyle320_50];
    DianJinTransitionParam *transitionParam = [[DianJinTransitionParam alloc] init];
    transitionParam.animationType = kDJTransitionCube;
    transitionParam.animationSubType = kDJTransitionFromTop;
    transitionParam.duration = 1.0;
    [_banner setupTransition:transitionParam];
    [settingView addSubview:_banner];
    offsetY = 50;
#endif

    if (!isPad()) {
        UIGlossyButton* btnBack = [[UIGlossyButton alloc]initWithFrame:CGRectMake(220, offsetY, 80, 30)];
        [btnBack setTitle:@"返回游戏" forState:UIControlStateNormal];
        [btnBack addTarget:self action:@selector(onClickBack) forControlEvents:UIControlEventTouchUpInside];
        
        [btnBack useWhiteLabel: YES];
        btnBack.tintColor = [UIColor brownColor];
        [btnBack setShadow:[UIColor blackColor] opacity:0.8 offset:CGSizeMake(0, 1) blurRadius: 4];
        [btnBack setGradientType:kUIGlossyButtonGradientTypeLinearSmoothBrightToNormal];
        [settingView addSubview:btnBack];
    }
    
    UIGlossyButton* btnMB = [[UIGlossyButton alloc]initWithFrame:CGRectMake(20, offsetY, 80, 30)];
    [btnMB setTitle:@"获取M币" forState:UIControlStateNormal];
    [btnMB addTarget:self action:@selector(onClickMB) forControlEvents:UIControlEventTouchUpInside];
    [btnMB useWhiteLabel: YES];
    btnMB.tintColor = [UIColor brownColor];
	[btnMB setShadow:[UIColor blackColor] opacity:0.8 offset:CGSizeMake(0, 1) blurRadius: 4];
    [btnMB setGradientType:kUIGlossyButtonGradientTypeLinearSmoothBrightToNormal];
    [settingView addSubview:btnMB];
    
    labelMB = [[UILabel alloc]initWithFrame:CGRectMake(100, offsetY, 100, 30)];
    labelMB.backgroundColor = [UIColor clearColor];
    [settingView addSubview:labelMB];
    
    offsetY += 30;
    
    m_tableView = [[UITableView alloc]initWithFrame:CGRectMake(0, offsetY, 320, 430) style:UITableViewStyleGrouped];
    m_tableView.delegate = self;
    m_tableView.dataSource = self;
    m_tableView.backgroundColor = [UIColor colorWithRed:240.0 / 255 green:248.0 / 255 blue:1.0 alpha:1.0];
    [m_tableView setBackgroundView:nil];
    [settingView addSubview:m_tableView];
    
    
    UIImageView* bgImage = [[UIImageView alloc]initWithImage:[UIImage imageNamed:@"bg2"]];
    bgImage.frame = CGRectMake(0, 0, frame.size.width, frame.size.height);
    [self addSubview:bgImage];
    
    UILabel* modeLabel = [[UILabel alloc]initWithFrame:CGRectMake(10, 30, 70, 24)];
    modeLabel.text = @"战斗模式:";
    modeLabel.font = [UIFont systemFontOfSize:15];
    modeLabel.backgroundColor = [UIColor clearColor];
    [settingView addSubview:modeLabel];
    
    switchMode = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    switchMode.frame = CGRectMake(80, 30, 70, 24);
    
    [switchMode setTitle:(g_isClassicMode ? @"回合制" : @"即时制") forState:UIControlStateNormal];
    [switchMode setTitle:(g_isClassicMode ? @"回合制" : @"即时制") forState:UIControlStateHighlighted];
    [switchMode addTarget:self  action:@selector(onClickMode) forControlEvents:UIControlEventTouchUpInside];
    switchMode.alpha = 0.8;
    [settingView addSubview:switchMode];
    
    UILabel* joystickLabel = [[UILabel alloc]initWithFrame:CGRectMake(10, 62, 70, 24)];
    joystickLabel.text = @"显示摇杆:";
    joystickLabel.backgroundColor = [UIColor clearColor];
    joystickLabel.font = [UIFont systemFontOfSize:15];
    [settingView addSubview:joystickLabel];
    
    UISwitch* joystickBtn = [[UISwitch alloc]initWithFrame:CGRectMake(80, 65, 40, 20)];
    joystickBtn.on = g_useJoyStick ? YES : NO;
    
    [joystickBtn addTarget:self  action:@selector(onClickJoystick) forControlEvents:UIControlEventTouchUpInside];
    joystickBtn.alpha = 0.8;
    [settingView addSubview:joystickBtn];
    
    UIButton* feedBack = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    feedBack.frame = CGRectMake(10, 95, 70, 24);
    [feedBack setTitle:@"bug反馈" forState:UIControlStateNormal];
    [feedBack setTitle:@"bug反馈" forState:UIControlStateHighlighted];
    feedBack.alpha = 0.8;
    [feedBack addTarget:self  action:@selector(onClickFeedBack) forControlEvents:UIControlEventTouchUpInside];
    [settingView addSubview:feedBack];
    
    UIButton* btnBBS = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    btnBBS.frame = CGRectMake(90, 95, 70, 24);
    [btnBBS setTitle:@"论坛交流" forState:UIControlStateNormal];
    [btnBBS setTitle:@"论坛交流" forState:UIControlStateHighlighted];
    btnBBS.alpha = 0.8;
    [btnBBS addTarget:self  action:@selector(onClickBBS) forControlEvents:UIControlEventTouchUpInside];
    [settingView addSubview:btnBBS];
    
    hackLabel = [[UILabel alloc]initWithFrame:CGRectMake(10, 130, 150, 24)];
    hackLabel.text = [self testHackEnable] ? @"金手指功能:(已开启)" : @"金手指功能:(未开启)";
    hackLabel.backgroundColor = [UIColor clearColor];
    hackLabel.font = [UIFont systemFontOfSize:15];
    [settingView addSubview:hackLabel];
    
    UILabel* moveLabel = [[UILabel alloc]initWithFrame:CGRectMake(10, 160, 70, 24)];
    moveLabel.text = @"移动模式:";
    moveLabel.font = [UIFont systemFontOfSize:15];
    moveLabel.backgroundColor = [UIColor clearColor];
    [settingView addSubview:moveLabel];
    
    moveButton = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    moveButton.frame = CGRectMake(80, 160, 70, 24);
    
    [moveButton setTitle:(isFlyMode() ? @"穿墙" : @"正常") forState:UIControlStateNormal];
    [moveButton setTitle:(isFlyMode() ? @"穿墙" : @"正常") forState:UIControlStateHighlighted];
    [moveButton addTarget:self  action:@selector(onClickMove) forControlEvents:UIControlEventTouchUpInside];
    moveButton.alpha = 0.8;
    [settingView addSubview:moveButton];
    
    UIButton* uplevBtn = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    uplevBtn.frame = CGRectMake(10, 190, 100, 24);
    [uplevBtn setTitle:@"全角色升级" forState:UIControlStateNormal];
    [uplevBtn setTitle:@"全角色升级" forState:UIControlStateHighlighted];
    uplevBtn.alpha = 0.8;
    [uplevBtn addTarget:self  action:@selector(onClickLevelUp) forControlEvents:UIControlEventTouchUpInside];
    [settingView addSubview:uplevBtn];
    
    UIButton* addMoneyBtn = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    addMoneyBtn.frame = CGRectMake(10, 220, 100, 24);
    [addMoneyBtn setTitle:@"加5000金钱" forState:UIControlStateNormal];
    [addMoneyBtn setTitle:@"加5000金钱" forState:UIControlStateHighlighted];
    addMoneyBtn.alpha = 0.8;
    [addMoneyBtn addTarget:self  action:@selector(onClickAddMoney) forControlEvents:UIControlEventTouchUpInside];
    [settingView addSubview:addMoneyBtn];
    
    g_currentMB = [[NSUserDefaults standardUserDefaults]integerForKey:@"MB"];
    UILabel* label = [[UILabel alloc]initWithFrame:CGRectMake(10, 240, 100, 30)];
    label.backgroundColor = [UIColor clearColor];
    label.tag = 400;
    label.font = [UIFont systemFontOfSize:15];
    label.text = [NSString stringWithFormat:@"(当前元宝:%d)", g_currentMB];
    [settingView addSubview:label];
    
#ifdef APP_FOR_APPSTORE
    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(onPurchaseOk) name:kIAPSucceededNotification object:nil];
    [[InAppPurchaseMgr sharedInstance]loadStore];
#endif

    [self setView:settingView];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.contentSizeForViewInPopover = CGSizeMake(320, 480);
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (NSUInteger)supportedInterfaceOrientations
{
    return UIInterfaceOrientationMaskPortrait;
}

-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];

    g_currentMB = [[NSUserDefaults standardUserDefaults]integerForKey:@"MB"];
    [self updateMB];

    [m_tableView reloadData];
}

-(void)updateMB
{
    labelMB.text = [NSString stringWithFormat:@"当前M币: %d", g_currentMB];
}

-(void)onClickMB
{
    [[DianJinOfferPlatform defaultPlatform]showOfferWall: self delegate:self];
}

-(void)onClickBack
{
    if (isPad()) {
    } else {
        if ([[[UIDevice currentDevice]systemVersion]floatValue] >= 5.0) {
            [self dismissViewControllerAnimated:YES completion:nil];
        } else {
            [self dismissModalViewControllerAnimated:YES];
        }
    }
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 2;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
{
    if (section == 0) {
        return @"游戏扩展";
    } else if (section == 1) {
        return @"其他";
    }
    return @"";
}

- (NSString *)tableView:(UITableView *)tableView titleForFooterInSection:(NSInteger)section
{
    return @"";
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    if (section == 0) {
        return 2;
    } else if (section == 1) {
        return 4;
    }
    return 0;
}

- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section
{
    return 40;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 44;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell* cell = nil;
    
    if (indexPath.section == 0) {
        static NSString* cellIdent = @"MyCellMy";
        cell = [tableView dequeueReusableCellWithIdentifier:cellIdent];
        if (!cell) {
            cell = [[UITableViewCell alloc]initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:cellIdent];
            cell.textLabel.font = [UIFont systemFontOfSize:17.0];
            cell.selectionStyle = UITableViewCellSelectionStyleGray;
            
            UIImageView* imageLock = [[UIImageView alloc]initWithImage:[UIImage imageNamed:@"gui_lock.png"]];
            imageLock.frame = CGRectMake(280, 5, 15, 15);
            imageLock.tag = 101;
            [cell.contentView addSubview:imageLock];
        }
        
        UIImageView* imageLock = (UIImageView*)[cell.contentView viewWithTag:101];
        if (indexPath.row == 0) {
            imageLock.hidden = YES;
            cell.textLabel.text = @"金庸原版";
            cell.detailTextLabel.text = @"怀旧推荐";
        } else if (indexPath.row == 1) {
            imageLock.hidden = [self isPurchase:kPurchaseCanglong alert:NO];
            cell.textLabel.text = @"苍龙逐日";
            cell.detailTextLabel.text = @"v1.2美化版，最完美版本，没有之一";
        }
        cell.accessoryType = (indexPath.row == g_app_type) ? UITableViewCellAccessoryCheckmark : UITableViewCellAccessoryNone;
    } else if (indexPath.section == 1) {
        static NSString* cellIdent = @"MyCellGongl";
        cell = [tableView dequeueReusableCellWithIdentifier:cellIdent];
        if (!cell) {
            cell = [[UITableViewCell alloc]initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:cellIdent];
            cell.textLabel.font = [UIFont systemFontOfSize:17.0];
            cell.selectionStyle = UITableViewCellSelectionStyleGray;
            cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
        }
        
        switch (indexPath.row) {
            case 0:
                cell.textLabel.text = @"意见反馈";
                cell.detailTextLabel.text = @"此非即时通讯，您可以通过微博与我们联系";
                break;
            case 1:
                cell.textLabel.text = @"新浪微博(@BananaStudio)";
                cell.detailTextLabel.text = @"关注我们，了解最新游戏发布及版本更新";
                break;
            case 2:
                cell.textLabel.text = @"腾讯微博(@BananaStudio)";
                cell.detailTextLabel.text = @"关注我们，了解最新游戏发布及版本更新";
                break;
            case 3:
                cell.textLabel.text = @"精品推荐";
                cell.detailTextLabel.text = @"";
                break;
            default:
                break;
        }
    }
    
    return cell;
}

-(BOOL)isPurchase:(NSString*)purchaseKey alert:(BOOL)alert
{
    NSUserDefaults* defaults = [NSUserDefaults standardUserDefaults];
    BOOL isPurchase = [defaults boolForKey:purchaseKey];
    if (isPurchase) {
        return YES;
    }
    
    if (alert) {
#ifdef APP_FOR_APPSTORE
        [[InAppPurchaseMgr sharedInstance]purchaseProUpgrade];
#else
        m_purchaseKey = purchaseKey;
        costMB = 50;

        NSString* title = [NSString stringWithFormat:@"消耗%dM币解锁此项，您可以通过下载精品推荐应用的方式免费获取MB，当前MB:%d", costMB, g_currentMB];
        UIAlertView* alertView = [[UIAlertView alloc]initWithTitle:@"提示" message:title delegate:self cancelButtonTitle:@"知道了" otherButtonTitles:@"解锁", @"获取MB", nil];
        [alertView show];
#endif
    }
    
    return NO;
}

- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath
{
    return NO;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [tableView deselectRowAtIndexPath:indexPath animated:YES];

    if (indexPath.section == 0) {
        int mod = 0;
        switch (indexPath.row) {
            case 0:
                mod = 0;
                break;
            case 1:
                if (![self isPurchase:kPurchaseCanglong alert:YES]) {
                    return;
                }
                mod = 1;
                break;
            default:
                break;
        }

        if (mod != g_app_type) {
            g_app_type = mod;
            [m_tableView reloadData];
            [[NSUserDefaults standardUserDefaults]setInteger:g_app_type forKey:@"mod"];
            [[NSUserDefaults standardUserDefaults]synchronize];
            
            UIAlertView* alert = [[UIAlertView alloc]initWithTitle:@"信息" message:@"选择完成，请重启游戏" delegate:self cancelButtonTitle:@"确定" otherButtonTitles:nil];
            alert.tag = 999;
            [alert show];
            
            [self onClickBack];
        }
    
    } else if (indexPath.section == 1) {
        switch (indexPath.row) {
            case 0:
                [UMFeedback showFeedback:self withAppkey:kUMengAppKey];
                break;
            case 1:
                [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"http://weibo.com/bananastudi0"]];
                break;
            case 2:
                [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"http://t.qq.com/BananaStudio"]];
                break;
            case 3:
                [[DianJinOfferPlatform defaultPlatform]showOfferWall: self delegate:self];
                break;
                break;
            default:
                break;
        }
    }
}

- (void)appActivatedDidFinish:(NSDictionary *)resultDic
{
    NSLog(@"%@", resultDic);
    NSNumber *result = [resultDic objectForKey:@"result"];
    if ([result boolValue]) {
        NSNumber *awardAmount = [resultDic objectForKey:@"awardAmount"];
        NSString *identifier = [resultDic objectForKey:@"identifier"];
        NSLog(@"app identifier = %@", identifier);
        g_currentMB += [awardAmount floatValue];
        [[NSUserDefaults standardUserDefaults]setInteger:g_currentMB forKey:@"MB"];
        [[NSUserDefaults standardUserDefaults]synchronize];
        
        [self updateMB];
    }
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex;
{
    if (alertView.tag == 999) {
        exit(0);
    } else {
        if (buttonIndex == 1) {
            if (g_currentMB < costMB) {
                UIAlertView* alert = [[UIAlertView alloc]initWithTitle:@"错误" message:[NSString stringWithFormat:@"M币不足，当前M币:%d",g_currentMB] delegate:nil cancelButtonTitle:@"知道了" otherButtonTitles:nil];
                [alert show];
            } else {
                g_currentMB -= costMB;
                [[NSUserDefaults standardUserDefaults]setInteger:g_currentMB forKey:@"MB"];
                [[NSUserDefaults standardUserDefaults] setBool:YES forKey:m_purchaseKey];
                [[NSUserDefaults standardUserDefaults]synchronize];
                [self updateMB];
                costMB = 0;
            }
        } else if (buttonIndex == 2) {
            [[DianJinOfferPlatform defaultPlatform]showOfferWall: self delegate:self];
        }
    }
}





-(void)updateMBInfo
{
    if (g_currentMB >= 100) {
        NSUserDefaults* defaults = [NSUserDefaults standardUserDefaults];
        if (defaults) {
            hackLabel.text = @"金手指功能:(已开启)";
            [[NSUserDefaults standardUserDefaults] setObject:[[UIDevice currentDevice] uniqueDeviceIdentifier] forKey:kRemoveAdsFlag];
            [[NSUserDefaults standardUserDefaults] synchronize];
        }
    }
    
    UILabel* label = (UILabel*)[self viewWithTag:400];
    label.text = [NSString stringWithFormat:@"(当前M币:%d)", g_currentMB];
    
    [[NSUserDefaults standardUserDefaults]setInteger:g_currentMB forKey:@"MB"];
    [[NSUserDefaults standardUserDefaults] synchronize];
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
    
    if (g_currentMB >= 100) {
        NSUserDefaults* defaults = [NSUserDefaults standardUserDefaults];
        if (defaults) {
            hackLabel.text = @"金手指功能:(已开启)";
            [[NSUserDefaults standardUserDefaults] setObject:[[UIDevice currentDevice] uniqueDeviceIdentifier] forKey:kRemoveAdsFlag];
            [[NSUserDefaults standardUserDefaults] synchronize];
        }
        return YES;
    }
    
#ifdef APP_FOR_APPSTORE
    [[InAppPurchaseMgr sharedInstance]purchaseProUpgrade];
#else
    [[DianJinOfferPlatform defaultPlatform] getBalance:self];
    
    NSString* title = [NSString stringWithFormat:@"当您获得100元宝时将自动开启金手指功能。您可以通过点击广告条安装精品应用的方式免费获取元宝。 (当前元宝:%d)", g_currentMB];
    UIAlertView* alert = [[UIAlertView alloc]initWithTitle:@"提示" message:title delegate:nil cancelButtonTitle:@"知道了" otherButtonTitles:nil, nil];
    [alert show];
#endif
    return NO;
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
    NSLog(@"%@", resultDic);
    NSNumber *result = [resultDic objectForKey:@"result"];
    if ([result boolValue]) {
        NSNumber *awardAmount = [resultDic objectForKey:@"awardAmount"];
        NSString *identifier = [resultDic objectForKey:@"identifier"];
        NSLog(@"app identifier = %@", identifier);
        g_currentMB += [awardAmount floatValue];
        [systemView updateMBInfo];
    }
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





if (textView == nil) {
    textView = [[UITextView alloc]initWithFrame:CGRectMake(180, 50, 300, 270)];
    NSString* text = [NSString stringWithContentsOfFile:@"faq.txt" encoding:NSUTF8StringEncoding error:nil];
    if (text) {
        textView.text = text;
        textView.editable = NO;
        textView.alpha = 0.8;
    }
@end
