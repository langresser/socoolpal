#import <UIKit/UIKit.h>

#include "video/SDL_sysvideo.h"

@interface SDL_uikitviewcontroller : UIViewController {
}

- (id)initWithSDLWindow:(SDL_Window *)_window;
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)orient;
- (void)loadView;
@end
