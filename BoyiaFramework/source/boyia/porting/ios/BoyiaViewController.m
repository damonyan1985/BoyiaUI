//
//  BoyiaViewController.m
//  core
//
//  Created by yanbo on 2021/8/20.
//

@import MetalKit;
@import GLKit;

#import "BoyiaViewController.h"
#import "BoyiaView.h"
#import "ShaderType.h"
#import "IOSRenderer.h"

@interface BoyiaViewController ()

@property (nonatomic, strong) BoyiaView* boyiaView;

@property (nonatomic, strong) CADisplayLink* displayLink;

@property (nonatomic, strong) IOSRenderer* renderer;

@end

@implementation BoyiaViewController

-(instancetype)init {
  return [self initWithMetal:nil bundle:nil];
}

-(instancetype)initWithMetal:(NSString*)nibName
                         bundle:(NSBundle*)nibBundle {
  self = [super initWithNibName:nibName bundle:nibBundle];
//  if (self) {
//      [self metalInit];
//  }

  return self;
}

-(void)viewDidLoad {
    [super viewDidLoad];
    NSLog(@"Hello BoyiaViewController");
    
    self.boyiaView = [[BoyiaView alloc] initWithFrame:self.view.bounds];
    
    self.view = self.boyiaView;
    
    CAMetalLayer* layer = [self.boyiaView metalLayer];
    //self.renderer = [[IOSRenderer alloc] initWithLayer:layer];
    
    self.renderer = [IOSRenderer initRenderer:layer];
        
    self.displayLink = [CADisplayLink displayLinkWithTarget:self
                                                   selector:@selector(render:)];
    [self.displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSRunLoopCommonModes];
}

// 收到vsync信号之后进行渲染
-(void)render:(CADisplayLink*)link {

    //[self.renderer render];
    // 避免一直渲染造成性能损耗
    self.displayLink.paused = YES;
}

-(void)await {
    if (self.displayLink != nil) {
        self.displayLink.paused = NO;
    }
}

-(void)touchEvent:(int)type withEvent:(UIEvent*)event  {
    NSSet* allTouches = [event allTouches];
    UITouch* touch = [allTouches anyObject];
    CGPoint touchPoint = [touch preciseLocationInView:[touch view]];
    if (self.renderer) {
        [self.renderer handleTouchEvent:type x:touchPoint.x y:touchPoint.y];
    }
    NSLog(@"event: x=%f and y=%f", touchPoint.x, touchPoint.y);
}

-(void)touchesBegan:(NSSet*)touches withEvent:(UIEvent*)event {
    [self touchEvent:0 withEvent:event];
}

-(void)touchesEnded:(NSSet*)touches withEvent:(UIEvent*)event {
    [self touchEvent:1 withEvent:event];
}

-(void)touchesMoved:(NSSet*)touches withEvent:(UIEvent*)event {
    [self touchEvent:2 withEvent:event];
}

@end
