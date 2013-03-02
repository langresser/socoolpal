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
#import "TextViewController.h"

#include "hack.h"

#define kPurchaseCanglong @"kPurchaseCanglong"
#define kPurchaseCangyan @"kPurchaseCangyan"

BOOL g_isClassicMode = YES;
int g_currentMB = 0;
int g_joystickType = 0;
BOOL g_useJoyStick = YES;

int g_app_type;

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
    int height = 320;
    if (isPad()) {
        height = 600;
    }
    
    if (isPad()) {
        settingView = [[UIView alloc]initWithFrame:CGRectMake(0, 0, 800, height)];
    } else {
        settingView = [[UIView alloc]initWithFrame:CGRectMake(0, 0, 480, height)];
    }
    settingView.backgroundColor = [UIColor colorWithRed:240.0 / 255 green:248.0 / 255 blue:1.0 alpha:1.0];
    
    float offsetY = 0;
#ifndef APP_FOR_APPSTORE
    _banner = [[DianJinOfferBanner alloc] initWithOfferBanner:CGPointMake(0, 0) style:kDJBannerStyle320_50];
    DianJinTransitionParam *transitionParam = [[DianJinTransitionParam alloc] init];
    transitionParam.animationType = kDJTransitionCube;
    transitionParam.animationSubType = kDJTransitionFromTop;
    transitionParam.duration = 1.0;
    [_banner setupTransition:transitionParam];
    
    if (isPad()) {
        _banner.frame = CGRectMake(0, 0, 240, 50);
    } else {
        _banner.center = CGPointMake(240, 25);
    }
    
    [settingView addSubview:_banner];
    [_banner startWithTimeInterval:30 delegate:self];
    offsetY = 50;
#endif

    if (!isPad()) {
        UIGlossyButton* btnBack = [[UIGlossyButton alloc]initWithFrame:CGRectMake(380, offsetY, 80, 30)];
        [btnBack setTitle:@"返回游戏" forState:UIControlStateNormal];
        [btnBack addTarget:self action:@selector(onClickBack) forControlEvents:UIControlEventTouchUpInside];
        
        [btnBack useWhiteLabel: YES];
        btnBack.tintColor = [UIColor brownColor];
        [btnBack setShadow:[UIColor blackColor] opacity:0.8 offset:CGSizeMake(0, 1) blurRadius: 4];
        [btnBack setGradientType:kUIGlossyButtonGradientTypeLinearSmoothBrightToNormal];
        [settingView addSubview:btnBack];
    }
    
    UIGlossyButton* btnMB = [[UIGlossyButton alloc]initWithFrame:CGRectMake(20, offsetY, 80, 30)];
    [btnMB setTitle:@"获取元宝" forState:UIControlStateNormal];
    [btnMB addTarget:self action:@selector(onClickMB) forControlEvents:UIControlEventTouchUpInside];
    [btnMB useWhiteLabel: YES];
    btnMB.tintColor = [UIColor brownColor];
	[btnMB setShadow:[UIColor blackColor] opacity:0.8 offset:CGSizeMake(0, 1) blurRadius: 4];
    [btnMB setGradientType:kUIGlossyButtonGradientTypeLinearSmoothBrightToNormal];
    [settingView addSubview:btnMB];
    
    labelMB = [[UILabel alloc]initWithFrame:CGRectMake(100, offsetY, 100, 30)];
    labelMB.backgroundColor = [UIColor clearColor];
    labelMB.text = [NSString stringWithFormat:@"(当前:%d)", g_currentMB];
    [settingView addSubview:labelMB];
    
    offsetY += 30;
    
    if (isPad()) {
        m_tableView = [[UITableView alloc]initWithFrame:CGRectMake(0, offsetY, 700, height - 50) style:UITableViewStyleGrouped];
    } else {
        m_tableView = [[UITableView alloc]initWithFrame:CGRectMake(0, offsetY, 480, height - 50) style:UITableViewStyleGrouped];
    }
    m_tableView.delegate = self;
    m_tableView.dataSource = self;
    m_tableView.backgroundColor = [UIColor colorWithRed:240.0 / 255 green:248.0 / 255 blue:1.0 alpha:1.0];
    [m_tableView setBackgroundView:nil];
    [settingView addSubview:m_tableView];
    
#ifdef APP_FOR_APPSTORE
    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(onPurchaseOk) name:kIAPSucceededNotification object:nil];
    [[InAppPurchaseMgr sharedInstance]loadStore];
#else
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(appActivatedDidFinish:) name:kDJAppActivateDidFinish object:nil];
#endif

    [self setView:settingView];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.contentSizeForViewInPopover = CGSizeMake(800, 600);
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotate
{
    return YES;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationLandscapeLeft || interfaceOrientation == UIInterfaceOrientationLandscapeRight);
}

- (NSUInteger)supportedInterfaceOrientations
{
    return UIInterfaceOrientationMaskLandscape;
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
    labelMB.text = [NSString stringWithFormat:@"(当前:%d)", g_currentMB];
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
    return 3;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
{
    if (section == 0) {
        return @"游戏扩展";
    } else if (section == 1) {
        return @"金手指";
    } else if (section == 2) {
        return @"其他";
    }
    return @"";
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    if (section == 0) {
        return 2;
    } else if (section == 1) {
        return 3;
    } else if (section == 2) {
        return 6;
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
            imageLock.frame = CGRectMake(430, 5, 15, 15);
            imageLock.tag = 101;
            [cell.contentView addSubview:imageLock];
        }
        
        UIImageView* imageLock = (UIImageView*)[cell.contentView viewWithTag:101];
        if (indexPath.row == 0) {
            imageLock.hidden = YES;
            cell.textLabel.text = @"即时战斗模式";
            cell.detailTextLabel.text = @"";
            cell.accessoryType = g_isClassicMode == 1 ? UITableViewCellAccessoryNone : UITableViewCellAccessoryCheckmark;
        } else if (indexPath.row == 1) {
            imageLock.hidden = YES;
            cell.textLabel.text = @"显示摇杆";
            cell.detailTextLabel.text = @"";
            cell.accessoryType = g_useJoyStick == 1 ? UITableViewCellAccessoryCheckmark : UITableViewCellAccessoryNone;
        }
    } else if (indexPath.section == 1) {
        static NSString* cellIdent = @"MyCellHack";
        cell = [tableView dequeueReusableCellWithIdentifier:cellIdent];
        if (!cell) {
            cell = [[UITableViewCell alloc]initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:cellIdent];
            cell.textLabel.font = [UIFont systemFontOfSize:17.0];
            cell.selectionStyle = UITableViewCellSelectionStyleGray;
            
            UIImageView* imageLock = [[UIImageView alloc]initWithImage:[UIImage imageNamed:@"gui_lock.png"]];
            imageLock.frame = CGRectMake(430, 5, 15, 15);
            imageLock.tag = 101;
            [cell.contentView addSubview:imageLock];
        }
        
        UIImageView* imageLock = (UIImageView*)[cell.contentView viewWithTag:101];
        if (indexPath.row == 0) {
            imageLock.hidden = [self isHackEnable:FALSE];
            cell.textLabel.text = @"开启穿墙模式";
            cell.detailTextLabel.text = @"自由的飞翔";
            cell.accessoryType = isFlyMode() ? UITableViewCellAccessoryCheckmark : UITableViewCellAccessoryNone;
        } else if (indexPath.row == 1) {
            imageLock.hidden = [self isHackEnable:FALSE];
            cell.textLabel.text = @"全角色升级";
            cell.detailTextLabel.text = @"一秒变成高富帅";
            cell.accessoryType = UITableViewCellAccessoryNone;
        } else if (indexPath.row == 2) {
            imageLock.hidden = [self isHackEnable:FALSE];
            cell.textLabel.text = @"加5000金钱";
            cell.detailTextLabel.text = @"手头紧了吗";
            cell.accessoryType = UITableViewCellAccessoryNone;
        }
  //      cell.accessoryType = (indexPath.row == g_app_type) ? UITableViewCellAccessoryCheckmark : UITableViewCellAccessoryNone;
    } else if (indexPath.section == 2) {
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
                cell.textLabel.text = @"游戏攻略";
                cell.detailTextLabel.text = @"";
                break;
            case 1:
                cell.textLabel.text = @"游戏FAQ";
                cell.detailTextLabel.text = @"";
                break;
            case 2:
                cell.textLabel.text = @"意见反馈";
                cell.detailTextLabel.text = @"此非即时通讯，您可以通过微博与我们联系";
                break;
            case 3:
                cell.textLabel.text = @"新浪微博(@BananaStudio)";
                cell.detailTextLabel.text = @"关注我们，了解最新游戏发布及版本更新";
                break;
            case 4:
                cell.textLabel.text = @"腾讯微博(@BananaStudio)";
                cell.detailTextLabel.text = @"关注我们，了解最新游戏发布及版本更新";
                break;
            case 5:
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
        switch (indexPath.row) {
            case 0:
            {
                g_isClassicMode = !g_isClassicMode;
                NSUserDefaults* defaults = [NSUserDefaults standardUserDefaults];
                if (defaults) {
                    [defaults setInteger:(g_isClassicMode ? 1 : 2) forKey:@"BattleMode"];
                    [defaults synchronize];
                }
                
                [tableView reloadSections:[NSIndexSet indexSetWithIndex:0] withRowAnimation:UITableViewRowAnimationAutomatic];
            }
                break;
            case 1:
            {
                g_useJoyStick = !g_useJoyStick;
                
                NSUserDefaults* defaults = [NSUserDefaults standardUserDefaults];
                if (defaults) {
                    [defaults setInteger:(g_useJoyStick ? 1 : 2) forKey:@"JoystickMode"];
                    [defaults synchronize];
                }
                
                if (g_useJoyStick) {
                    showJoystick();
                } else {
                    hideJoystick();
                }
                
                [tableView reloadSections:[NSIndexSet indexSetWithIndex:0] withRowAnimation:UITableViewRowAnimationAutomatic];
            }
                break;
            default:
                break;
        }
    } else if (indexPath.section == 1) {
        switch (indexPath.row) {
            case 0:
                if ([self isHackEnable:YES]) {
                    setFlyMode(!isFlyMode());
                    [tableView reloadSections:[NSIndexSet indexSetWithIndex:1] withRowAnimation:UITableViewRowAnimationAutomatic];
                }
                break;
            case 1:
                if ([self isHackEnable:YES]) {
                    uplevel();
                    [tableView reloadSections:[NSIndexSet indexSetWithIndex:1] withRowAnimation:UITableViewRowAnimationAutomatic];
                }
                break;
            case 2:
                if ([self isHackEnable:YES]) {
                    addMoney();
                    [tableView reloadSections:[NSIndexSet indexSetWithIndex:1] withRowAnimation:UITableViewRowAnimationAutomatic];
                }
                break;
            default:
                break;
        }
    } else if (indexPath.section == 2) {
        switch (indexPath.row) {
            case 0:
            {
                TextViewController* vc = [[TextViewController alloc]initWithNibName:nil bundle:nil];
                vc.text = [NSString stringWithContentsOfFile:@"gl.txt" encoding:NSUTF8StringEncoding error:nil];
                [self presentModalViewController:vc animated:YES];
            }
                break;
            case 1:
            {
                TextViewController* vc = [[TextViewController alloc]initWithNibName:nil bundle:nil];
                vc.text = [NSString stringWithContentsOfFile:@"faq.txt" encoding:NSUTF8StringEncoding error:nil];
                [self presentModalViewController:vc animated:YES];
            }
                break;
            case 2:
                [UMFeedback showFeedback:self withAppkey:kUMengAppKey];
                break;
            case 3:
                [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"http://weibo.com/bananastudi0"]];
                break;
            case 4:
                [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"http://t.qq.com/BananaStudio"]];
                break;
            case 5:
                [[DianJinOfferPlatform defaultPlatform]showOfferWall: self delegate:self];
                break;
            default:
                break;
        }
    }
}

- (void)appActivatedDidFinish:(NSNotification *)notice;
{
    [self updateMB];
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex;
{
    if (alertView.tag == 100) {
        if (buttonIndex == 1) {
            if (g_currentMB < 100) {
                UIAlertView* alert = [[UIAlertView alloc]initWithTitle:@"错误" message:[NSString stringWithFormat:@"元宝不足，当前元宝:%d",g_currentMB] delegate:nil cancelButtonTitle:@"知道了" otherButtonTitles:nil];
                [alert show];
            } else {
                g_currentMB -= 100;
                [[NSUserDefaults standardUserDefaults]setInteger:g_currentMB forKey:@"MB"];
                [[NSUserDefaults standardUserDefaults]setObject:[[UIDevice currentDevice] uniqueDeviceIdentifier] forKey:kRemoveAdsFlag];
                [[NSUserDefaults standardUserDefaults]synchronize];
                [self updateMB];
                costMB = 0;
            }
        } else if (buttonIndex == 2) {
            [[DianJinOfferPlatform defaultPlatform]showOfferWall: self delegate:self];
        }
    }
}

-(BOOL)isHackEnable : (BOOL) testFlag
{
    NSString* flag = [[NSUserDefaults standardUserDefaults] stringForKey:kRemoveAdsFlag];
    if (flag && [flag isEqualToString:[[UIDevice currentDevice] uniqueDeviceIdentifier]]) {
        return YES;
    }
    
    if (g_currentMB >= 100) {
        NSUserDefaults* defaults = [NSUserDefaults standardUserDefaults];
        if (defaults) {
            g_currentMB-=100;
            [[NSUserDefaults standardUserDefaults] setInteger:g_currentMB forKey:@"MB"];
            [[NSUserDefaults standardUserDefaults] setObject:[[UIDevice currentDevice] uniqueDeviceIdentifier] forKey:kRemoveAdsFlag];
            [[NSUserDefaults standardUserDefaults] synchronize];
        }
        return YES;
    }
    
    if (testFlag) {
        NSString* title = [NSString stringWithFormat:@"消耗100元宝解锁金手指功能。您可以通过点击广告条安装精品应用的方式免费获取元宝。 (当前元宝:%d)", g_currentMB];
        UIAlertView* alert = [[UIAlertView alloc]initWithTitle:@"提示" message:title delegate:self cancelButtonTitle:@"知道了" otherButtonTitles:@"解锁", @"获取元宝", nil];
        alert.tag = 100;
        [alert show];
    }

    return NO;
}
@end
