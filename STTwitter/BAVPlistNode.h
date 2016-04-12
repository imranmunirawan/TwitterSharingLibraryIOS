


#import <Foundation/Foundation.h>

@interface BAVPlistNode : NSObject
@property (nonatomic, copy) NSString *key;
@property (nonatomic, copy) NSString *type;
@property (nonatomic, copy) NSObject *value;
@property (nonatomic, copy) NSArray *children;
@property (nonatomic, assign, getter = isCollection) bool collection;

+ (instancetype)plistNodeFromObject:(id)object key:(NSString *)key;
@end
