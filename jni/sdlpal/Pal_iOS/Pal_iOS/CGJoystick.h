//
//  CGJoystick.h
//  Pal_iOS
//
//  Created by 王 佳 on 12-7-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

#define DIR_UP 1
#define DIR_DOWN 2
#define DIR_LEFT 3
#define DIR_RIGHT 4

@interface CGJoystick : UIView
{
    UIImage* stickBase;
    UIImage* stickUp;
    UIImage* stickDown;
    UIImage* stickLeft;
    UIImage* stickRight;
    
    int stickDir;
}
@end
