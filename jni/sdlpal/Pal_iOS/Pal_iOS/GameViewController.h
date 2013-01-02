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
    UIButton* btnA;
    UIButton* btnB;
    
    UIButton* btnMenu;
    
    SettingViewController* settingVC;
    UIPopoverController * popoverVC;
}

-(void)showSettingPopup:(BOOL)show;
@end
