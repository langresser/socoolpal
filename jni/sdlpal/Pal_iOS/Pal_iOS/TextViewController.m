//
//  TextViewController.m
//  Pal_iOS
//
//  Created by Liu Jun on 13-2-24.
//
//

#import "TextViewController.h"

@interface TextViewController ()

@end

@implementation TextViewController
@synthesize text;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    textView = [[UITextView alloc]initWithFrame:[UIScreen mainScreen].bounds];
    [self.view addSubview:textView];
    
    textView.text = text;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
