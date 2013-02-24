//
//  GameViewController.h
//  SDLJY_iOS
//
//  Created by 佳 王 on 12-11-25.
//  Copyright (c) 2012年 佳 王. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SDL_uikitviewcontroller.h"
#import "CGJoystick.h"
#import "SettingViewController.h"

@interface GameViewController : SDL_uikitviewcontroller<UIPopoverControllerDelegate>
{
    CGJoystick* joystick;
    
    UIButton* btnMenu;
    UIButton* btnBack;
    UIButton* btnSearch;
    UIButton* btnGameMenu;
    
    SettingViewController* settingVC;
    UIPopoverController * popoverVC;
}

-(void)showSettingPopup:(BOOL)show;
-(void)showJoystick;
-(void)hideJoystick;

-(void)showSearchButton;
-(void)hideSearchButton;
-(void)showBackButton;
-(void)hideBackButton;
-(void)showGameMenu;
-(void)hideGameMenu;
@end
