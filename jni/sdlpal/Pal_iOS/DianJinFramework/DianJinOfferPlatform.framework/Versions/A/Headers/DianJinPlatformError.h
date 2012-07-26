//
//  DianJinPlatformError.h
//  DianJinOfferPlatform
//
//  Created by zhuang zi jiao on 12-2-10.
//  Copyright 2012 NetDragon WebSoft Inc.. All rights reserved.
//

/*
 该头文件定义的返回的错误代码编号
 */

#define DIAN_JIN_ERROR_JSON_ANALYSIS_FAILED				-4					/**< json数据解析失败>*/
#define DIAN_JIN_ERROR_NO_SET_APP_ID_OR_KEY				-3					/**< 没有设置appid或appkey >*/
#define DIAN_JIN_ERROR_NETWORK_FAIL						-2					/**< 网络连接错误 >*/
#define DIAN_JIN_ERROR_UNKNOWN							-1					/**< 未知错误 >*/

#define DIAN_JIN_NO_ERROR								0					/**< 没有错误 >*/

#define DIAN_JIN_ERROR_PACKAGE_INVALID					1					/**< 数据包不全、丢失或无效 >*/
#define DIAN_JIN_ERROR_SESSIONID_INVALID				2					/**< SessionId（用户的会话标识）无效 >*/
#define DIAN_JIN_ERROR_ACT_INVALID						3					/**< 无效的接口编号 >*/
#define DIAN_JIN_ERROR_ACT_DISABLE						4					/**< 接口已经停用需要升级客户端 >*/
#define DIAN_JIN_ERROR_PACKAGE_DECRYPT_FAILED			5					/**< 数据包体解密失败 >*/
#define DIAN_JIN_ERROR_PARAM_ERROR						6					/**< 参数值错误或非法，请检查参数值是否有效 >*/
#define DIAN_JIN_RETURN_SDK_VERSION_INVALID				7					/**< SDK版本号无效 >*/


#define DIAN_JIN_ERROR_SERVER_SQL_ERROR					900					/**< 数据库操作出错 >*/
#define DIAN_JIN_ERROR_PACKAGE_LENGTH_TOO_LONG			996					/**< 发送的请求数据长度太长 >*/
#define DIAN_JIN_ERROR_SERVER_UNKNOWN_ERROR				997					/**< 未知的服务器错误 >*/
#define DIAN_JIN_ERROR_SERVER_MAINTENANCE				998					/**< 服务器维护 >*/
#define DIAN_JIN_ERROR_SERVER_INTERNAL_ERROR			999					/**< 服务器内部错误 >*/

#define DIAN_JIN_ERROR_USER_NOT_AUTHORIZED				1004				/**< 该用户未授权接入（AppId,AppKey无效）>*/

#define DIAN_JIN_ERROR_GET_BALANCE_FAILED				5001				/**< 获取余额失败 >*/

#define DIAN_JIN_ERROR_REQUES_CONSUNE					6001				/**< 支付请求失败 >*/
#define DIAN_JIN_ERROR_BALANCE_NO_ENOUGH				6002				/**< 余额不足 >*/
#define DIAN_JIN_ERROR_ACCOUNT_NO_EXIST					6003				/**< 帐号不存在 >*/
#define DIAN_JIN_ERROR_ORDER_SERIAL_REPEAT				6004				/**< 订单号重复 >*/
#define DIAN_JIN_ERROR_BEYOND_LARGEST_AMOUNT			6005				/**< 一次性交易超出最大限定金额 >*/
#define DIAN_JIN_ERROR_CONSUME_ID_NO_EXIST				6006				/**< 不存在该类型的消费动作ID >*/
