//
//  PSCCustomBookmarkBarButtonItem.m
//  PSPDFCatalog
//
//  Copyright (c) 2012-2014 PSPDFKit GmbH. All rights reserved.
//
//  The PSPDFKit Sample applications are licensed with a modified BSD license.
//  Please see License for details. This notice may not be removed from this file.
//

#import "PSCCustomBookmarkBarButtonItem.h"

// Simple subclass, replacing the image.
@implementation PSCCustomBookmarkBarButtonItem

// We are lazy and use a systemItem for the example.
- (UIBarButtonSystemItem)systemItem {
    BOOL hasBookmark = [self bookmarkNumberForVisiblePages] != nil;
    return hasBookmark ? UIBarButtonSystemItemBookmarks : UIBarButtonSystemItemTrash;
}

// Image has priority, so nil that out.
- (UIImage *)image {
    return nil;
}

@end
