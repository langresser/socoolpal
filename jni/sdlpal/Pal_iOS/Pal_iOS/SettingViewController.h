//
//  SettingViewController.h
//  MD
//
//  Created by 王 佳 on 12-9-5.
//  Copyright (c) 2012年 Gingco.Net New Media GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "util.h"
#import <DianJinOfferPlatform/DianJinOfferPlatform.h>
#import <DianJinOfferPlatform/DianJinBannerSubViewProperty.h>
#import <DianJinOfferPlatform/DianJinTransitionParam.h>
#import <DianJinOfferPlatform/DianJinOfferPlatformProtocol.h>
#import <DianJinOfferPlatform/DianJinAdBanner.h>
#import <DianJinOfferPlatform/DianJinOfferBanner.h>

#define kUseCPC 0

@interface SettingViewController : UIViewController<UITableViewDataSource, UITableViewDelegate, UIAlertViewDelegate, DianJinOfferPlatformProtocol, DianJinAdBannerDelegate>
{
    UIView* settingView;

#ifndef APP_FOR_APPSTORE
    DianJinOfferBanner *_bannerOffer;
    DianJinAdBanner *_banner;
#endif
    UITableView* m_tableView;
    
    UILabel* labelMB;
    
    int costMB;
    NSString* m_purchaseKey;
    
    BOOL isFAQ;
}

-(BOOL)isHackEnable:(BOOL)testFlag;
@end
