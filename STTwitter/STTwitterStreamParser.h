

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, STTwitterStreamJSONType) {
    STTwitterStreamJSONTypeTweet,
    STTwitterStreamJSONTypeFriendsLists,
    STTwitterStreamJSONTypeDelete,
    STTwitterStreamJSONTypeScrubGeo,
    STTwitterStreamJSONTypeLimit,
    STTwitterStreamJSONTypeDisconnect,
    STTwitterStreamJSONTypeWarning,
    STTwitterStreamJSONTypeEvent,
    STTwitterStreamJSONTypeStatusWithheld,
    STTwitterStreamJSONTypeUserWithheld,
    STTwitterStreamJSONTypeControl,
    STTwitterStreamJSONTypeUnsupported,
};

extern NSString *NSStringFromSTTwitterStreamJSONType(STTwitterStreamJSONType type);

@interface STTwitterStreamParser : NSObject

- (void)parseWithStreamData:(NSData *)data
            parsedJSONBlock:(void (^)(NSDictionary *json, STTwitterStreamJSONType type))parsedJsonBlock;

@end
