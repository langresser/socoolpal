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
        jsBg = [[UIImageView alloc]initWithImage:[UIImage imageNamed:@"SkillOperate"]];
        jsBg.frame = CGRectMake(0, 0, frame.size.width, frame.size.height);

        btnMain = [[UIButton alloc]initWithFrame:CGRectMake(50, 50, 50, 50)];
        [btnMain setImage:[UIImage imageNamed:@"expoint1"] forState:UIControlStateNormal];
        [btnMain setImage:[UIImage imageNamed:@"expoint3"] forState:UIControlStateHighlighted];
        [btnMain addTarget:self action:@selector(onClickMain) forControlEvents:UIControlEventTouchUpInside];

        btnUp = [[UIButton alloc]initWithFrame:CGRectMake(0, 0, 50, 50)];
        [btnUp setImage:[UIImage imageNamed:@"systembtnnormal"] forState:UIControlStateNormal];
        [btnUp setImage:[UIImage imageNamed:@"systembtnmboss"] forState:UIControlStateHighlighted];
        [btnUp addTarget:self action:@selector(onClickUp) forControlEvents:UIControlEventTouchUpInside];

        btnMid = [[UIButton alloc]initWithFrame:CGRectMake(0, 0, 50, 50)];
        [btnMid setImage:[UIImage imageNamed:@"expoint1"] forState:UIControlStateNormal];
        [btnMid setImage:[UIImage imageNamed:@"expoint2"] forState:UIControlStateHighlighted];
        [btnMid addTarget:self action:@selector(onClickMid) forControlEvents:UIControlEventTouchUpInside];
        
        btnDown = [[UIButton alloc]initWithFrame:CGRectMake(0, 0, 50, 50)];
        [btnDown setImage:[UIImage imageNamed:@"BackBtnNormal"] forState:UIControlStateNormal];
        [btnDown setImage:[UIImage imageNamed:@"BackBtnClick"] forState:UIControlStateHighlighted];
        [btnDown addTarget:self action:@selector(onClickDown) forControlEvents:UIControlEventTouchUpInside];
        
        [self addSubview:jsBg];
        
        [self addSubview:btnMain];
        
        [self addSubview:btnUp];
        [self addSubview:btnMid];
        [self addSubview:btnDown];
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
