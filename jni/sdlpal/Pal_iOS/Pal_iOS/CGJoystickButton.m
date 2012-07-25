//
//  CGJoystickButton.m
//  Pal_iOS
//
//  Created by 王 佳 on 12-7-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "CGJoystickButton.h"
#include "main.h"

@implementation CGJoystickButton

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
        
        
//        [self addSubview:jsBg];
        
        [self addSubview:btnMain];
        
//        [self addSubview:btnUp];
//        [self addSubview:btnMid];
//        [self addSubview:btnDown];
    }
    return self;
}

-(void)onClickMain
{
    extern BOOL PAL_Search(VOID);
    PAL_Search();
}

-(void)onClickUp
{
}

-(void)onClickMid
{
}

-(void)onClickDown
{
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

@end
