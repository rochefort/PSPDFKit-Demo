//
//  PSPDFNoteAnnotationViewController.h
//  PSPDFKit
//
//  Copyright (c) 2012-2014 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import "PSPDFKitGlobal.h"
#import "PSPDFStyleable.h"
#import "PSPDFBaseViewController.h"

@class PSPDFGradientView, PSPDFAnnotation, PSPDFPageView, PSPDFNoteAnnotationViewController;

@protocol PSPDFNoteAnnotationViewControllerDelegate <PSPDFOverridable>

@optional

/// Called when the `noteController` has deleted the annotation.
- (void)noteAnnotationController:(PSPDFNoteAnnotationViewController *)noteController didDeleteAnnotation:(PSPDFAnnotation *)annotation;

/// Called when the `noteController` has cleared the contents of the annotation.
- (void)noteAnnotationController:(PSPDFNoteAnnotationViewController *)noteController didClearContentsForAnnotation:(PSPDFAnnotation *)annotation;

/// Called when the `noteController` changes the annotation look. (color/iconName)
- (void)noteAnnotationController:(PSPDFNoteAnnotationViewController *)noteController didChangeAnnotation:(PSPDFAnnotation *)annotation;

/// Called before the `noteController` is closed.
- (void)noteAnnotationController:(PSPDFNoteAnnotationViewController *)noteController willDismissWithAnnotation:(PSPDFAnnotation *)annotation;

@end

/// Note annotation controller for editing `PSPDFObjectsAnnotationKey`.
/// For note annotations, special options will be displayed.
@interface PSPDFNoteAnnotationViewController : PSPDFBaseViewController <PSPDFStyleable>

/// Initializes with annotation, allows to override the editable state.
- (id)initWithAnnotation:(PSPDFAnnotation *)annotation editable:(BOOL)allowEditing;

/// Initializes with annotation, automatically sets the editable state.
- (id)initWithAnnotation:(PSPDFAnnotation *)annotation;

/// Attached annotation. All types are allowed.
@property (nonatomic, strong) PSPDFAnnotation *annotation;

/// If NO, the Edit/Delete buttons are not displayed and the text will be readonly.
/// @note While you could set `allowEditing` here with a value different than the annotation, it's not advised to do so as the content won't be saved.
/// Use `annotation.isEditable` && `[self.document.editableAnnotationTypes containsObject:annotation.typeString]` to test for edit capabilities.
@property (nonatomic, assign) BOOL allowEditing;

/// If YES, the edit button will be displayed to show color/icon editing. Defaults to YES.
/// Will be ignored if `allowEditing` is NO or annotation type is not `PSPDFAnnotationTypeNote`.
@property (nonatomic, assign) BOOL showColorAndIconOptions;

/// Shows the copy button. Disabled by default for space reasons (and because copying text is easy)
@property (nonatomic, assign) BOOL showCopyButton;

/// Allow to customize the textView. (font etc)
/// Created in `viewDidLoad`.
/// @note If you want to customize the font, override `textViewFont`.
@property (nonatomic, strong, readonly) UITextView *textView;

/// Set a global block that allows to customize the `UITextView` and other properties of `PSPDFNoteAnnotationViewController`.
/// Will be called in `viewWillAppear:`. This is the best way to customize the font.
+ (void)setTextViewCustomizationBlock:(void (^)(PSPDFNoteAnnotationViewController *))block;

/// Attached delegate.
@property (nonatomic, weak) IBOutlet id<PSPDFNoteAnnotationViewControllerDelegate> delegate;

@end


@interface PSPDFNoteAnnotationViewController (SubclassingHooks)

// Called when we're about to show the annotation delete menu.
- (void)deleteAnnotation:(UIBarButtonItem *)barButtonItem;

// Will delete annotation (note) or clear note text (any other type) without confirmation.
- (void)deleteOrClearAnnotationWithoutConfirmation;

// Returns "Delete Note", "Delete Free Text", "Delete Highlight" etc.
- (NSString *)deleteAnnotationActionTitle;

// Sets the text view as first responder and enables editing if allowed.
- (BOOL)beginEditing;

// Called as we update the text view.
- (void)updateTextView;

// Creates the font for the text view (adaptive to iOS 7 content size)
- (UIFont *)textViewFont;

// Background gradient.
@property (nonatomic, strong) PSPDFGradientView *backgroundView;

// Option view (note annotations)
@property (nonatomic, strong) UIView *optionsView;

// Tap gesture on the textView to enable/disable edit mode.
@property (nonatomic, strong) UITapGestureRecognizer *tapGesture;

@end
