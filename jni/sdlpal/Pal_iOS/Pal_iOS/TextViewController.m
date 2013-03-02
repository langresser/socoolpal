//
//  TextViewController.m
//  Pal_iOS
//
//  Created by Liu Jun on 13-2-24.
//
//

#import "TextViewController.h"
#import "UIGlossyButton.h"
#import "UIView+LayerEffects.h"

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
    self.view.backgroundColor = [UIColor whiteColor];
    // Do any additional setup after loading the view from its nib.
    CGRect rect = [UIScreen mainScreen].bounds;
    rect.origin.y += 50;
    rect.size.height -= 80;
    textView = [[UITextView alloc]initWithFrame:rect];
    [textView setEditable:NO];
    [self.view addSubview:textView];
    
    UIGlossyButton* btnBack = [[UIGlossyButton alloc]initWithFrame:CGRectMake(10, 10, 80, 30)];
    [btnBack setTitle:@"返回游戏" forState:UIControlStateNormal];
    [btnBack addTarget:self action:@selector(onClickBack) forControlEvents:UIControlEventTouchUpInside];
    
    [btnBack useWhiteLabel: YES];
    btnBack.tintColor = [UIColor brownColor];
    [btnBack setShadow:[UIColor blackColor] opacity:0.8 offset:CGSizeMake(0, 1) blurRadius: 4];
    [btnBack setGradientType:kUIGlossyButtonGradientTypeLinearSmoothBrightToNormal];
    [self.view addSubview:btnBack];

    textView.text = text;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void)onClickBack
{
    [self dismissModalViewControllerAnimated:YES];
}
@end
