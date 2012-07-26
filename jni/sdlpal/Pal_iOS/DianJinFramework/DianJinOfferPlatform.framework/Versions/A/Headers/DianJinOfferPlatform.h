//
//  DianJinOfferPlatform.h
//  DianJinOfferPlatform
//
//  Created by zhuang zi jiao on 12-2-10.
//  Copyright 2012 NetDragon WebSoft Inc.. All rights reserved.
//

typedef enum _DIAN_JIN_BACKGROUND_COLOR {
	kDJBlueColor = 0,
	kDJBlackColor,
	kDJBrownColor,
	kDJGreenColor,
	kDJOrangeColor,
	kDJRosyColor
}DIAN_JIN_BACKGROUND_COLOR;

@interface DianJinOfferPlatform : NSObject {

}

/**
 @brief 获取DianJinOffer的实例对象
 */
+ (DianJinOfferPlatform *)defaultPlatform;

#pragma mark -
#pragma mark version
/**
 @brief 获取DianJinOffer的版本号
 */
+ (NSString *)version;

#pragma mark -
#pragma mark set appId and appKey

/**
 @brief 设置应用Id及设置应用密钥
 @param appId 应用程序id，需要向用户中心申请，合法的id大于0
 @param appKey 第三方应用程序密钥，appKey未系统分配给第三方的应用程序密钥，第三方需要向平台提供方申请，并设置到平台上
 @result 设置是否成功
 */
- (BOOL)setAppId:(int)appId andSetAppKey:(NSString *)appKey;

/**
 @brief 获取appId，需要预先设置
 @result 返回appId
 */
- (int)getAppId;

#pragma mark -
#pragma mark set Interface Orientation

/**
 @brief 设定offerView方向，默认为UIInterfaceOrientationPortrait
 */
- (void)setOfferViewOrientation:(UIInterfaceOrientation)orientation;

/**
 @brief 设定offerView是否自动旋转，默认为不自动旋转
 */
- (void)setOfferViewAutoRotate:(BOOL)isAutoRotate;

/**
 @brief 相关背景颜色，默认为kDJBlueColor
 */
- (void)setOfferViewColor:(DIAN_JIN_BACKGROUND_COLOR)type;

#pragma mark -
#pragma mark show offer view

/**
 @brief  显示推广墙
 @param	 parent 显示视图的父视图指针，父视图必须为UIViewController或其子类
 @note	 建议尽量使用该接口显示推广墙
 @result 错误码 错误码详细说明请查看DianJinPlatformError.h文件
 */
- (int)showOfferWall:(UIViewController *)parent delegate:(id)delegate;

/**
 @brief  显示推广墙
 @param  delegate 获取推广墙关闭事件,如果不想获取可以传nil进去。详细请查看DianJinOfferPlatformProtocol.h文件
 @note	 当接入的应用不方便提供UIViewController类时(比如:游戏接入)可以调用本接口
 @result 错误码 错误码详细说明请查看DianJinPlatformError.h文件
 */
- (int)presentOfferWall:(id)delegate;

#pragma mark -
#pragma mark get balance

/**
 @brief 获取本机余额
 @param delegate 回调对象 delegate详细请查看DianJinOfferPlatformProtocol.h文件
 @result 返回错误码 错误码详细说明请查看DianJinPlatformError.h文件
 */
- (int)getBalance:(id)delegate;

/**
 @brief 取消获取本机余额请求
 @param delegate 回调对象
 */
- (void)cancelGetBalance:(id)delegate;

#pragma mark -
#pragma mark consume

/**
 @brief 用户消费
 @param amount 该次交易的金额大小.
 @param delegate 回调对象 delegate详细请查看DianJinOfferPlatformProtocol.h文件
 @result 返回错误码 错误码详细说明请查看DianJinPlatformError.h文件
 */
- (int)consume:(float)amount delegate:(id)delegate;

/**
 @brief 取消消费请求
 @param delegate 回调对象
 */
- (void)cancelConsume:(id)delegate;

@end
