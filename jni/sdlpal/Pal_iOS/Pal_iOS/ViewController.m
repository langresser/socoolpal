#if 0
#include "SDL_config.h"

#if SDL_VIDEO_DRIVER_UIKIT

#include "SDL_video.h"
#include "SDL_assert.h"
#include "SDL_hints.h"
#include "video/SDL_sysvideo.h"
#include "events/SDL_events_c.h"

#import "ViewController.h"
#include "video/uikit/SDL_uikitvideo.h"

@implementation SDL_uikitviewcontroller
- (id)initWithSDLWindow:(SDL_Window *)_window
{
    self = [self init];
    if (self == nil) {
        return nil;
    }
    return self;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)orient
{
    if (orient == UIInterfaceOrientationLandscapeLeft || orient == UIInterfaceOrientationLandscapeLeft) {
        return YES;
    } else {
        return NO;
    }
}

- (void)loadView
{
    // do nothing.
}
#endif /* SDL_VIDEO_DRIVER_UIKIT */

@end
#endif