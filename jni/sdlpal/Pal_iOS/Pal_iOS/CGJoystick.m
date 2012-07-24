//
//  CGJoystick.m
//  Pal_iOS
//
//  Created by 王 佳 on 12-7-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "CGJoystick.h"
#import <QuartzCore/QuartzCore.h>
#include "input.h"

@implementation CGJoystick

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
        stickBase = [UIImage imageNamed:@"integerrockerbg"];
        stickUp = [UIImage imageNamed:@"up"];
        stickDown = [UIImage imageNamed:@"down"];
        stickLeft = [UIImage imageNamed:@"left"];
        stickRight = [UIImage imageNamed:@"right"];
//        joystickBase = [[UIImageView alloc] initWithImage:image];
//        joystickBase.frame = CGRectMake(0, 0, frame.size.width, frame.size.height);
//        joystickBase.backgroundColor = [UIColor clearColor];
//        [self addSubview:joystickBase];
    }
    return self;
}

-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch* touch = [[event allTouches]anyObject];
    CGPoint point = [touch locationInView:self];
    int dir = [self getDirByPoint:point];
    if (stickDir != dir) {
        [self setNeedsDisplay];
        stickDir = dir;
    }
    
    [self doMove:stickDir];
}

-(void)doMove:(int)dir
{
    switch (dir) {
        case DIR_UP:
            g_InputState.dir = kDirNorth;
            break;
        case DIR_DOWN:
            g_InputState.dir = kDirSouth;
            break;
        case DIR_LEFT:
            g_InputState.dir = kDirWest;
            break;
        case DIR_RIGHT:
            g_InputState.dir = kDirEast;
            break;
        default:
            g_InputState.dir = kDirUnknown;
            break;
    }
}

-(int)getDirByPoint:(CGPoint)point
{
    int dir = 0;
    if (point.x > 30 && point.x <= 50 && point.y >= 0 && point.y <= 50) {
        dir = DIR_UP;
    } else if (point.x >= 30 && point.x <= 50 && point.y >= 50 && point.y <= 100) {
        dir = DIR_DOWN;
    } else if (point.x >= 0 && point.x <= 50 && point.y >= 40 && point.y <= 60) {
        dir = DIR_LEFT;
    } else if (point.x >= 50 && point.x <= 100 && point.y >= 40 && point.y <= 60) {
        dir = DIR_RIGHT;
    } else {
        dir = 0;
    }
    
    return dir;
}

-(void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch* touch = [[event allTouches]anyObject];
    CGPoint point = [touch locationInView:self];
    int dir = [self getDirByPoint:point];
    if (stickDir != dir) {
        [self setNeedsDisplay];
        stickDir = dir;
    }
    
    [self doMove:stickDir];
}

-(void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    if (stickDir != 0) {
        [self setNeedsDisplay];
    }
    stickDir = 0;
    [self doMove:0];
}

-(void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
    if (stickDir != 0) {
        [self setNeedsDisplay];
    }
    stickDir = 0;
}


// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
//    CGContextRef context = UIGraphicsGetCurrentContext();
    [stickBase drawInRect:rect];
    
    switch (stickDir) {
        case DIR_UP:
            [stickUp drawInRect:CGRectMake(30, 0, 20, 50)];
            break;
        case DIR_DOWN:
            [stickDown drawInRect:CGRectMake(30, 50, 20, 50)];
            break;
        case DIR_LEFT:
            [stickLeft drawInRect:CGRectMake(0, 40, 50, 20)];
            break;
        case DIR_RIGHT:
            [stickRight drawInRect:CGRectMake(50, 40, 50, 20)];
            break;
        default:
            break;
    }
}


@end
