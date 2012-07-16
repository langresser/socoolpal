//
//  DMTools.h
//
//  Copyright (c) 2012 Domob Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DMTools : NSObject

// 初始化开发者工具
- (id)initWithPublisherId:(NSString *)publisherId;

// 检查是否有评价提醒
- (void)checkRateInfo;

@end