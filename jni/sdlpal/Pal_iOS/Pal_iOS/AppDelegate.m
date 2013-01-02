#import "AppDelegate.h"
#import "GameViewController.h"
#import "MobClick.h"
#import "UMFeedback.h"

#ifndef APP_FOR_APPSTORE
    #import <DianJinOfferPlatform/DianJinOfferPlatform.h>
    #import <DianJinOfferPlatform/DianJinOfferBanner.h>
    #import <DianJinOfferPlatform/DianJinBannerSubViewProperty.h>
    #import <DianJinOfferPlatform/DianJinTransitionParam.h>
#endif

extern int g_app_type;
extern int g_isInBackground;

@implementation AppDelegate
// iOS 4.x
- (void)applicationWillEnterForeground:(UIApplication *)application
{
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    g_isInBackground = 1;
//    [super applicationWillResignActive:application];
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    g_isInBackground = 0;
 //   [super applicationDidBecomeActive:application];
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
}

// iOS 3.x
- (void)applicationWillTerminate:(UIApplication *)application
{
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions 
{
    //    [MobClick setLogEnabled:YES];
    [MobClick startWithAppkey:kUMengAppKey];
    [UMFeedback checkWithAppkey:kUMengAppKey];
    
#ifndef APP_FOR_APPSTORE
    // Override point for customization after application launch.
	[[DianJinOfferPlatform defaultPlatform] setAppId:kDianjinAppKey andSetAppKey:kDianjinAppSecrect];
	[[DianJinOfferPlatform defaultPlatform] setOfferViewColor:kDJBlueColor];
    [[DianJinOfferPlatform defaultPlatform] setOfferViewAutoRotate:YES];
#endif
    
    g_app_type = [[NSUserDefaults standardUserDefaults]integerForKey:@"mod"];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onRecNewMsg:) name:UMFBCheckFinishedNotification object:nil];

//    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
//    NSString  *plistPath = [paths objectAtIndex:0];
//    NSString* scriptDir = [plistPath stringByAppendingPathComponent:@"script"];
//    
//    NSFileManager* fm = [NSFileManager defaultManager];
//    [fm createDirectoryAtPath:scriptDir withIntermediateDirectories:YES attributes:nil error:nil];

    /* Keep the launch image up until we set a video mode */
    self.uiwindow = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    self.viewController = [[GameViewController alloc]init];
    uiwindow.rootViewController = viewController;

    /* Set working directory to resource path */
    [[NSFileManager defaultManager] changeCurrentDirectoryPath: [[NSBundle mainBundle] resourcePath]];

    [super application:application didFinishLaunchingWithOptions:launchOptions];

    [uiwindow makeKeyAndVisible];
    return TRUE;
}

-(void)beginAutoSave
{
    [NSTimer scheduledTimerWithTimeInterval:60 target:self selector:@selector(autoSave) userInfo:nil repeats:YES];
}

-(void)autoSave
{
}

-(void)onRecNewMsg:(NSNotification*)notification
{
    NSArray * newReplies = [notification.userInfo objectForKey:@"newReplies"];
    if (!newReplies) {
        return;
    }
    
    UIAlertView *alertView;
    NSString *title = [NSString stringWithFormat:@"有%d条新回复", [newReplies count]];
    NSMutableString *content = [NSMutableString string];
    for (int i = 0; i < [newReplies count]; i++) {
        NSString * dateTime = [[newReplies objectAtIndex:i] objectForKey:@"datetime"];
        NSString *_content = [[newReplies objectAtIndex:i] objectForKey:@"content"];
        [content appendString:[NSString stringWithFormat:@"%d: %@---%@\n", i+1, _content, dateTime]];
    }
    
    alertView = [[UIAlertView alloc] initWithTitle:title message:content delegate:self cancelButtonTitle:@"确定" otherButtonTitles:nil];
    ((UILabel *) [[alertView subviews] objectAtIndex:1]).textAlignment = NSTextAlignmentLeft ;
    [alertView show];
    
}
@end
