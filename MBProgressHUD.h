//
//  MBProgressHUD.h
//  Version 0.9.1
//  Created by Matej Bukovinski on 2.4.09.
//

// This code is distributed under the terms and conditions of the MIT license. 

// Copyright (c) 2009-2015 Matej Bukovinski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <CoreGraphics/CoreGraphics.h>

@class MBBackgroundView;
@protocol MBProgressHUDDelegate;


typedef NS_ENUM(NSInteger, MBProgressHUDMode) {
	/// UIActivityIndicatorView.
	MBProgressHUDModeIndeterminate,
	/// A round, pie-chart like, progress view.
	MBProgressHUDModeDeterminate,
	/// Horizontal progress bar.
	MBProgressHUDModeDeterminateHorizontalBar,
	/// Ring-shaped progress view.
	MBProgressHUDModeAnnularDeterminate,
	/// Shows a custom view.
	MBProgressHUDModeCustomView,
	/// Shows only labels.
	MBProgressHUDModeText
};

typedef NS_ENUM(NSInteger, MBProgressHUDAnimation) {
	/// Opacity animation
	MBProgressHUDAnimationFade,
	/// Opacity + scale animation
    MBProgressHUDAnimationZoom,
    /// Opacity + scale animation (zoom out style)
	MBProgressHUDAnimationZoomOut = MBProgressHUDAnimationZoom,
    /// Opacity + scale animation (zoom in style)
	MBProgressHUDAnimationZoomIn
};


/** 
 * Displays a simple HUD window containing a progress indicator and two optional labels for short messages.
 *
 * This is a simple drop-in class for displaying a progress HUD view similar to Apple's private UIProgressHUD class.
 * The MBProgressHUD window spans over the entire space given to it by the initWithFrame: constructor and catches all
 * user input on this region, thereby preventing the user operations on components below the view.
 *
 * @note To still allow touches to pass through the HUD, you can set hud.userInteractionEnabled = NO.
 * @attention MBProgressHUD is a UI class and should therefore only be accessed on the main thread.
 */
@interface MBProgressHUD : UIView

/**
 * Creates a new HUD, adds it to provided view and shows it. The counterpart to this method is hideHUDForView:animated:.
 *
 * @note This method sets removeFromSuperViewOnHide. The HUD will automatically be removed from the view hierarchy when hidden.
 *
 * @param view The view that the HUD will be added to
 * @param animated If set to YES the HUD will appear using the current animationType. If set to NO the HUD will not use
 * animations while appearing.
 * @return A reference to the created HUD.
 *
 * @see hideHUDForView:animated:
 * @see animationType
 */
+ (instancetype)showHUDAddedTo:(UIView *)view animated:(BOOL)animated;

/**
 * Finds the top-most HUD subview and hides it. The counterpart to this method is showHUDAddedTo:animated:.
 *
 * @note This method sets `removeFromSuperViewOnHide`. The HUD will automatically be removed from the view hierarchy when hidden.
 *
 * @param view The view that is going to be searched for a HUD subview.
 * @param animated If set to YES the HUD will disappear using the current animationType. If set to NO the HUD will not use
 * animations while disappearing.
 * @return YES if a HUD was found and removed, NO otherwise.
 *
 * @see showHUDAddedTo:animated:
 * @see animationType
 */
+ (BOOL)hideHUDForView:(UIView *)view animated:(BOOL)animated;

/**
 * Finds the top-most HUD subview and returns it. 
 *
 * @param view The view that is going to be searched.
 * @return A reference to the last HUD subview discovered.
 */
+ (instancetype)HUDForView:(UIView *)view;

/**
 * A convenience constructor that initializes the HUD with the view's bounds. Calls the designated constructor with
 * view.bounds as the parameter
 *
 * @param view The view instance that will provide the bounds for the HUD. Should be the same instance as
 * the HUD's superview (i.e., the view that the HUD will be added to).
 */
- (instancetype)initWithView:(UIView *)view;

/** 
 * Displays the HUD. 
 *
 * @note You need to make sure that the main thread completes its run loop soon after this method call so
 * the user interface can be updated. Call this method when your task is already set-up to be executed in a new thread
 * (e.g., when using something like NSOperation or calling an asynchronous call like NSURLRequest).
 *
 * @param animated If set to YES the HUD will appear using the current animationType. If set to NO the HUD will not use
 * animations while appearing.
 *
 * @see animationType
 */
- (void)showAnimated:(BOOL)animated;

/** 
 * Hides the HUD. This still calls the hudWasHidden: delegate. This is the counterpart of the show: method. Use it to
 * hide the HUD when your task completes.
 *
 * @param animated If set to YES the HUD will disappear using the current animationType. If set to NO the HUD will not use
 * animations while disappearing.
 *
 * @see animationType
 */
- (void)hideAnimated:(BOOL)animated;

/** 
 * Hides the HUD after a delay. This still calls the hudWasHidden: delegate. This is the counterpart of the show: method. Use it to
 * hide the HUD when your task completes.
 *
 * @param animated If set to YES the HUD will disappear using the current animationType. If set to NO the HUD will not use
 * animations while disappearing.
 * @param delay Delay in seconds until the HUD is hidden.
 *
 * @see animationType
 */
- (void)hideAnimated:(BOOL)animated afterDelay:(NSTimeInterval)delay;

/**
 * The HUD delegate object. Recives HUD state notifications.
 */
@property (weak, nonatomic) id<MBProgressHUDDelegate> delegate;

/** 
 * MBProgressHUD operation mode. The default is MBProgressHUDModeIndeterminate.
 */
@property (assign, nonatomic) MBProgressHUDMode mode;

/**
 * The animation type that should be used when the HUD is shown and hidden.
 */
@property (assign, nonatomic) MBProgressHUDAnimation animationType;

/**
 * The view containing the labels and indicator (or customView).
 */
@property (strong, nonatomic, readonly) MBBackgroundView *bezelView;

/**
 * The UIView (e.g., a UIImageView) to be shown when the HUD is in MBProgressHUDModeCustomView.
 * The view should implement intrinsicContentSize for proper sizing. For best results use approximately 37 by 37 pixel.
 */
@property (strong, nonatomic) UIView *customView;

/**
 * A label that holds an optional short message to be displayed below the activity indicator. The HUD is automatically resized to fit
 * the entire text.
 */
@property (strong, nonatomic, readonly) UILabel *label;

/**
 * A label that holds an optional details message displayed below the labelText message. The details text can span multiple lines.
 */
@property (strong, nonatomic, readonly) UILabel *detailsLabel;

/**
 * The bezel offset relative to the centre of the view.
 */
@property (assign, nonatomic) CGPoint offset;

/**
 * The amount of space between the HUD edge and the HUD elements (labels, indicators or custom views). 
 * This also represents the minimum bezel distance to the edge of the HUD view.
 * Defaults to 20.f
 */
@property (assign, nonatomic) CGFloat margin;

/**
 * The minimum size of the HUD bezel. Defaults to CGSizeZero (no minimum size).
 */
@property (assign, nonatomic) CGSize minSize;

/**
 * Force the HUD dimensions to be equal if possible.
 */
@property (assign, nonatomic, getter = isSquare) BOOL square;

/*
 * Grace period is the time (in seconds) that the invoked method may be run without 
 * showing the HUD. If the task finishes before the grace time runs out, the HUD will
 * not be shown at all. 
 * This may be used to prevent HUD display for very short tasks.
 * Defaults to 0 (no grace time).
 */
@property (assign, nonatomic) NSTimeInterval graceTime;

/**
 * The minimum time (in seconds) that the HUD is shown. 
 * This avoids the problem of the HUD being shown and than instantly hidden.
 * Defaults to 0 (no minimum show time).
 */
@property (assign, nonatomic) NSTimeInterval minShowTime;

/**
 * Removes the HUD from its parent view when hidden. 
 * Defaults to NO. 
 */
@property (assign, nonatomic) BOOL removeFromSuperViewOnHide;

/** 
 * The progress of the progress indicator, from 0.0 to 1.0. Defaults to 0.0. 
 */
@property (assign, nonatomic) float progress;

@end


@protocol MBProgressHUDDelegate <NSObject>

@optional

/** 
 * Called after the HUD was fully hidden from the screen. 
 */
- (void)hudWasHidden:(MBProgressHUD *)hud;

@end


/**
 * A progress view for showing definite progress by filling up a circle (pie chart).
 */
@interface MBRoundProgressView : UIView 

/**
 * Progress (0.0 to 1.0)
 */
@property (nonatomic, assign) float progress;

/**
 * Indicator progress color.
 * Defaults to white [UIColor whiteColor]
 */
@property (nonatomic, strong) UIColor *progressTintColor;

/**
 * Indicator background (non-progress) color.
 * Defaults to translucent white (alpha 0.1)
 */
@property (nonatomic, strong) UIColor *backgroundTintColor;

/*
 * Display mode - NO = round or YES = annular. Defaults to round.
 */
@property (nonatomic, assign, getter = isAnnular) BOOL annular;

@end


/**
 * A flat bar progress view. 
 */
@interface MBBarProgressView : UIView

/**
 * Progress (0.0 to 1.0)
 */
@property (nonatomic, assign) float progress;

/**
 * Bar border line color.
 * Defaults to white [UIColor whiteColor].
 */
@property (nonatomic, strong) UIColor *lineColor;

/**
 * Bar background color.
 * Defaults to clear [UIColor clearColor];
 */
@property (nonatomic, strong) UIColor *progressRemainingColor;

/**
 * Bar progress color.
 * Defaults to white [UIColor whiteColor].
 */
@property (nonatomic, strong) UIColor *progressColor;

@end


@interface MBBackgroundView : UIView

@end

@interface MBProgressHUD (Deprecated)

+ (NSArray *)allHUDsForView:(UIView *)view __attribute__((deprecated("Store references when using more than one HUD per view.")));
+ (NSUInteger)hideAllHUDsForView:(UIView *)view animated:(BOOL)animated __attribute__((deprecated("Store references when using more than one HUD per view.")));

- (id)initWithWindow:(UIWindow *)window __attribute__((deprecated("Use initWithView: instead.")));

- (void)show:(BOOL)animated __attribute__((deprecated("Use showAnimated: instead.")));
- (void)hide:(BOOL)animated __attribute__((deprecated("Use hideAnimated: instead.")));
- (void)hide:(BOOL)animated afterDelay:(NSTimeInterval)delay __attribute__((deprecated("Use hideAnimated:afterDelay: instead.")));

typedef void (^MBProgressHUDCompletionBlock)();

- (void)showWhileExecuting:(SEL)method onTarget:(id)target withObject:(id)object animated:(BOOL)animated __attribute__((deprecated("Use GCD directly.")));
- (void)showAnimated:(BOOL)animated whileExecutingBlock:(dispatch_block_t)block __attribute__((deprecated("Use GCD directly.")));
- (void)showAnimated:(BOOL)animated whileExecutingBlock:(dispatch_block_t)block completionBlock:(MBProgressHUDCompletionBlock)completion __attribute__((deprecated("Use GCD directly.")));
- (void)showAnimated:(BOOL)animated whileExecutingBlock:(dispatch_block_t)block onQueue:(dispatch_queue_t)queue __attribute__((deprecated("Use GCD directly.")));
- (void)showAnimated:(BOOL)animated whileExecutingBlock:(dispatch_block_t)block onQueue:(dispatch_queue_t)queue
     completionBlock:(MBProgressHUDCompletionBlock)completion __attribute__((deprecated("Use GCD directly.")));
@property (copy) MBProgressHUDCompletionBlock completionBlock __attribute__((deprecated("Use GCD directly.")));
@property (assign) BOOL taskInProgress __attribute__((deprecated("No longer needed for .")));

@property (nonatomic, copy) NSString *labelText __attribute__((deprecated("Use label.text instead.")));
@property (nonatomic, strong) UIFont *labelFont __attribute__((deprecated("Use label.font instead.")));
@property (nonatomic, strong) UIColor *labelColor __attribute__((deprecated("Use label.textColor instead.")));
@property (nonatomic, copy) NSString *detailsLabelText __attribute__((deprecated("Use detailsLabel.text instead.")));
@property (nonatomic, strong) UIFont *detailsLabelFont __attribute__((deprecated("Use detailsLabel.font instead.")));
@property (nonatomic, strong) UIColor *detailsLabelColor __attribute__((deprecated("Use detailsLabel.textColor instead.")));
@property (assign, nonatomic) CGFloat opacity __attribute__((deprecated("Customize bezelView properties instead.")));
@property (strong, nonatomic) UIColor *color __attribute__((deprecated("Customize bezelView properties instead.")));
@property (assign, nonatomic) CGFloat xOffset __attribute__((deprecated("Set offset.x instead.")));
@property (assign, nonatomic) CGFloat yOffset __attribute__((deprecated("Set offset.y instead.")));
@property (assign, nonatomic) CGFloat cornerRadius __attribute__((deprecated("Set bezelView.layer.cornerRadius instead.")));
@property (assign, nonatomic) BOOL dimBackground __attribute__((deprecated("Customize HUD backgroudn properties instead.")));
@property (strong, nonatomic) UIColor *activityIndicatorColor __attribute__((deprecated("Use UIAppearance to customize UIActivityIndicatorView.")));
@property (atomic, assign, readonly) CGSize size __attribute__((deprecated("Get the bezelView.frame.size instead.")));

@end
