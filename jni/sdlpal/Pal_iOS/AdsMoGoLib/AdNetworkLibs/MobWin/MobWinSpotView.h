//
//  MobWinSpotView.h
//  MobWinSDK
//
//  Created by Guo Zhao on on 11-12-7.
//  Copyright 2011 Tencent. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MobWinSpotViewDelegate.h"

@protocol MobWinSpotViewDelegate;

@interface MobWinSpotView : NSObject <MobWinSpotViewDelegate>

// 应用鉴权ID
// 详解：[必须设定]绑定应用的应用鉴权ID
@property (nonatomic, retain) NSString *adUnitID;

// 测试模式开关
// 默认测试模式关闭 adTestMode == NO
//
// 详解：[可选]测试模式开关，YES为测试模式，NO为发布模式，提交应用审核时请设置此参数为NO
@property (nonatomic, assign) bool adTestMode; 


// GPS精准广告定位模式开关
// 默认Gps模式开启 adGpsMode == YES
//
// 详解：[可选]精准定位模式开关，YES为精准定位模式，NO为非精准定位模式，建议设为精准定位模式，可以获取地域精准定向广告，提高广告的填充率，增加收益。
@property (nonatomic, assign) bool adGpsMode; 

// 提示语
// 默认提示语 adPromptTitle == 应用正在加载数据，请稍等
//
// 详解：位于时间进度条上面，开发者可设置一个友好的提示语，告诉用户当前后台在做什么
@property (nonatomic, retain) NSString *adPromptTitle; 

// 代理
// 
// 详解：Spot广告的传入回调代理
@property(nonatomic, assign) id<MobWinSpotViewDelegate> delegate;

// 广告拉取请求方法
// 
// 详解：[必选]发起拉取广告请求
- (void)startRequest;

// 广告展示请求方法
// 传入需要显示插播广告的UIViewController
// 
// 详解：[必选]发起展示广告请求, 必须传入用于显示插播广告的UIViewController
- (void)presentFromRootViewController:(UIViewController *)rootViewController;

@end
