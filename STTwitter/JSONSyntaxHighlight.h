

#import <Foundation/Foundation.h>

#if (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)
#import <UIKit/UIKit.h>
#else
#import <AppKit/AppKit.h>
#endif

@interface JSONSyntaxHighlight : NSObject

// Create the object by giving a JSON object, nil will be returned
// if the object can't be serialized
- (JSONSyntaxHighlight *)init;
- (JSONSyntaxHighlight *)initWithJSON:(id)JSON;

// Return an NSAttributedString with the highlighted JSON in a pretty format
- (NSAttributedString *)highlightJSON;

// Return an NSAttributedString with the highlighted JSON optionally pretty formatted
- (NSAttributedString *)highlightJSONWithPrettyPrint:(BOOL)prettyPrint;

// Fire a callback for every key item found in the parsed JSON, each callback
// is fired with the NSRange the substring appears in `self.parsedJSON`, as well
// as the NSString at that location.
- (void)enumerateMatchesWithIndentBlock:(void(^)(NSRange, NSString*))indentBlock
                               keyBlock:(void(^)(NSRange, NSString*))keyBlock
                             valueBlock:(void(^)(NSRange, NSString*))valueBlock
                               endBlock:(void(^)(NSRange, NSString*))endBlock;

// The JSON object, unmodified
@property (readonly, nonatomic, strong) id JSON;

// The serialized JSON string
@property (readonly, nonatomic, strong) NSString *parsedJSON;

// The attributes for Attributed Text
@property (nonatomic, strong) NSDictionary *keyAttributes;
@property (nonatomic, strong) NSDictionary *stringAttributes;
@property (nonatomic, strong) NSDictionary *nonStringAttributes;

// Platform dependent helper functions
#if (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)
+ (UIColor *)colorWithRGB:(NSInteger)rgbValue;
+ (UIColor *)colorWithRGB:(NSInteger)rgbValue alpha:(CGFloat)alpha;
#else
+ (NSColor *)colorWithRGB:(NSInteger)rgbValue;
+ (NSColor *)colorWithRGB:(NSInteger)rgbValue alpha:(CGFloat)alpha;
#endif

@end