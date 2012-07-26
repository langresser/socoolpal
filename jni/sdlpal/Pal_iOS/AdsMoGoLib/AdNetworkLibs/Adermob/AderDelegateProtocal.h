//
//  GAdsDelegateProtocal.h
//  GAds-SDK
//
//  Created by guowei huang on 12-2-23.
//  Copyright (c) 2012年 renren. All rights reserved.

#import <Foundation/Foundation.h>

@protocol AderDelegateProtocal <NSObject>
@optional

//成功接收并显示新广告后调用，count表示当前广告是第几条广告，SDK启动后从1开始，累加计数
- (void)didSucceedToReceiveAd:(NSInteger)count;

/*
 接受SDK返回的错误报告
 code 1: 参数错误
 code 2: 服务端错误
 code 3: 应用被冻结
 code 4: 无合适广告
 code 5: 应用账户不存在
 code 6: 频繁请求
*/
- (void) didReceiveError:(NSError *)error;

@end
