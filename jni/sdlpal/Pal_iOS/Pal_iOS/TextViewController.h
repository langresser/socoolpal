//
//  TextViewController.h
//  Pal_iOS
//
//  Created by Liu Jun on 13-2-24.
//
//

#import <UIKit/UIKit.h>

@interface TextViewController : UIViewController
{
    UITextView* textView;
    NSString* text;
}

@property(nonatomic, retain) NSString* text;
@end
