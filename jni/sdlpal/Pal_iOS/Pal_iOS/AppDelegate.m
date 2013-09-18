#import "AppDelegate.h"
#import "MobClick.h"
#import "UMFeedback.h"

#ifndef APP_FOR_APPSTORE
    #import <DianJinOfferPlatform/DianJinOfferPlatform.h>
    #import <DianJinOfferPlatform/DianJinOfferBanner.h>
    #import <DianJinOfferPlatform/DianJinBannerSubViewProperty.h>
    #import <DianJinOfferPlatform/DianJinTransitionParam.h>
#endif

extern int g_app_type;
int g_isInBackground;

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

+ (NSString *)getAppDelegateClassName
{
    /* subclassing notice: when you subclass this appdelegate, make sure to add a category to override
     this method and return the actual name of the delegate */
    return @"AppDelegate";
}

- (void)postFinishLaunch
{
    extern int SDL_mainLoop();
    /* run the user's application, passing argc and argv */
    SDL_iPhoneSetEventPump(SDL_TRUE);
    SDL_mainLoop();
    SDL_iPhoneSetEventPump(SDL_FALSE);
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
    //[[DianJinOfferPlatform defaultPlatform]floatLogoEnable:YES];
#endif
    
    g_app_type = [[NSUserDefaults standardUserDefaults]integerForKey:@"mod"];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onRecNewMsg:) name:UMFBCheckFinishedNotification object:nil];
    
    /* Set working directory to resource path */
    [[NSFileManager defaultManager] changeCurrentDirectoryPath: [[NSBundle mainBundle] resourcePath]];

//    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
//    NSString  *plistPath = [paths objectAtIndex:0];
//    NSString* scriptDir = [plistPath stringByAppendingPathComponent:@"script"];
//    
//    NSFileManager* fm = [NSFileManager defaultManager];
//    [fm createDirectoryAtPath:scriptDir withIntermediateDirectories:YES attributes:nil error:nil];

    /* Keep the launch image up until we set a video mode */
    self.uiwindow = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    self.viewController = [[GameViewController alloc]init];
    self.uiwindow.rootViewController = viewController;
    
    SDL_main(0, NULL);
    [self.uiwindow makeKeyAndVisible];
    
    [self performSelector:@selector(postFinishLaunch) withObject:nil afterDelay:0.0];
    return TRUE;
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
        if (_content == nil) {
            continue;
        }
        [content appendString:[NSString stringWithFormat:@"%d: %@---%@\n", i+1, _content, dateTime]];
    }
    
    alertView = [[UIAlertView alloc] initWithTitle:title message:content delegate:self cancelButtonTitle:@"确定" otherButtonTitles:nil];
    ((UILabel *) [[alertView subviews] objectAtIndex:1]).textAlignment = NSTextAlignmentLeft ;
    [alertView show];
    
}
@end
