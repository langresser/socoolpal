#if 0
#include "SDL_config.h"

#if SDL_VIDEO_DRIVER_UIKIT

#import "video/SDL_sysvideo.h"
#import "SDL_assert.h"
#import "SDL_hints.h"
#import "SDL_hints_c.h"

#import "video/uikit/SDL_uikitopenglview.h"
#import "events/SDL_events_c.h"
#import "video/uikit/jumphack.h"
#import "AppDelegate.h"
#include "main.h"

#ifdef main
#undef main
#endif

int main(int argc, char **argv)
{
    @autoreleasepool {        
        /* Give over control to run loop, SDLUIKitDelegate will handle most things from here */
        int ret = UIApplicationMain(argc, argv, NULL, @"SDLUIKitDelegate");
        return ret;
    }
}

static void SDL_IdleTimerDisabledChanged(const char *name, const char *oldValue, const char *newValue)
{
    SDL_assert(SDL_strcmp(name, SDL_HINT_IDLE_TIMER_DISABLED) == 0);
    
    BOOL disable = (*newValue != '0');
    [UIApplication sharedApplication].idleTimerDisabled = disable;
}

@implementation SDLUIKitDelegate
- (id)init
{
    self = [super init];
    return self;
}

- (void)postFinishLaunch
{
    /* register a callback for the idletimer hint */
    SDL_SetHint(SDL_HINT_IDLE_TIMER_DISABLED, "0");
    SDL_RegisterHintChangedCb(SDL_HINT_IDLE_TIMER_DISABLED, &SDL_IdleTimerDisabledChanged);
    
    WORD          wScreenWidth = 0, wScreenHeight = 0;
    
    UTIL_OpenLog();
    
    wScreenWidth = 480;
    wScreenHeight = 320;
    PAL_Init(wScreenWidth, wScreenHeight, TRUE);
    
    //
    // Show the trademark screen and splash screen
    //
    //   PAL_TrademarkScreen();
#ifndef _DEBUG
    PAL_SplashScreen();
#endif
    
    PAL_GameMain();
    /* exit, passing the return status from the user's application */
    // exit(exit_status);
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    /* Set working directory to resource path */
    [[NSFileManager defaultManager] changeCurrentDirectoryPath: [[NSBundle mainBundle] resourcePath]];
    
    [self performSelector:@selector(postFinishLaunch) withObject:nil afterDelay:0.0];
    
    return YES;
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    SDL_SendQuit();
    /* hack to prevent automatic termination.  See SDL_uikitevents.m for details */
    longjmp(*(jump_env()), 1);
}

- (void) applicationWillResignActive:(UIApplication*)application
{
    //NSLog(@"%@", NSStringFromSelector(_cmd));
    
    // Send every window on every screen a MINIMIZED event.
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    if (!_this) {
        return;
    }
    
    SDL_Window *window;
    for (window = _this->windows; window != nil; window = window->next) {
        SDL_SendWindowEvent(window, SDL_WINDOWEVENT_FOCUS_LOST, 0, 0);
        SDL_SendWindowEvent(window, SDL_WINDOWEVENT_MINIMIZED, 0, 0);
    }
}

- (void) applicationDidBecomeActive:(UIApplication*)application
{
    //NSLog(@"%@", NSStringFromSelector(_cmd));
    
    // Send every window on every screen a RESTORED event.
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    if (!_this) {
        return;
    }
    
    SDL_Window *window;
    for (window = _this->windows; window != nil; window = window->next) {
        SDL_SendWindowEvent(window, SDL_WINDOWEVENT_FOCUS_GAINED, 0, 0);
        SDL_SendWindowEvent(window, SDL_WINDOWEVENT_RESTORED, 0, 0);
    }
}

@end

#endif /* SDL_VIDEO_DRIVER_UIKIT */
#endif
