//
//  DianJinOfferPlatformProtocol.h
//  DianJinOfferPlatform
//
//  Created by zhuang zi jiao on 12-2-10.
//  Copyright 2012 NetDragon WebSoft Inc.. All rights reserved.
//

@protocol DianJinOfferPlatformProtocol<NSObject>

/**
 @brief 获取余额回调
 @param dict  通过key:result可以获得返回的结果,当返回结果为0时为正确可以通过key:balance获取到用户当前余额.
			  如果返回结果不为0可以通过查看DianJinPlatformError.h文件的错误码说明来确定错误类型
 */
- (void)getBalanceDidFinish:(NSDictionary *)dict;

/**
 @brief 消费回调
 @param dict 通过key:result可以获得返回的结果,当返回结果为0时为正确可以通过key:action获取当前的消费动作类型.
             如果返回结果不为0可以通过查看DianJinPlatformError.h文件的错误码说明来确定错误类型
 */
- (void)consumeDidFinish:(NSDictionary *)dict;

/**
 @brief 退出推广墙界面回调
 */
- (void)offerViewDidClose;

/**
 @brief 应用安装激活事件反馈
 @param dict 通过key:result可以获得返回的结果,当返回结果为YES时为激活成功，NO为激活失败。可以通过key:awardAmount获取当前激活应用的奖励金额.
 */
- (void)appActivatedDidFinish:(NSDictionary *)dict;

@end
