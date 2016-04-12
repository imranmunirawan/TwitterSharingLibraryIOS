

#import <Foundation/Foundation.h>
#import "STTwitterProtocol.h"

extern NS_ENUM(NSUInteger, STTwitterOSErrorCode) {
    STTwitterOSSystemCannotAccessTwitter = 0,
    STTwitterOSCannotFindTwitterAccount,
    STTwitterOSUserDeniedAccessToTheirAccounts,
    STTwitterOSNoTwitterAccountIsAvailable,
    STTwitterOSTwitterAccountInvalid
};

@class ACAccount;

extern const NSString *STTwitterOSInvalidatedAccount;

@interface STTwitterOS : NSObject <STTwitterProtocol>

@property (nonatomic) NSTimeInterval timeoutInSeconds;

+ (instancetype)twitterAPIOSWithAccount:(ACAccount *)account;
+ (instancetype)twitterAPIOSWithFirstAccount;

- (NSString *)username;
- (NSString *)userID;

// useful for the so-called 'OAuth Echo' https://dev.twitter.com/twitter-kit/ios/oauth-echo

- (NSDictionary *)OAuthEchoHeadersToVerifyCredentials;

@end
