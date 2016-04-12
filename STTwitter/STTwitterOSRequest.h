

#import <Foundation/Foundation.h>
#import "STTwitterRequestProtocol.h"

@class ACAccount;

@interface STTwitterOSRequest : NSObject <NSURLSessionDataDelegate, STTwitterRequestProtocol>

- (instancetype)initWithAPIResource:(NSString *)resource
                      baseURLString:(NSString *)baseURLString
                         httpMethod:(NSInteger)httpMethod
                         parameters:(NSDictionary *)params
                            account:(ACAccount *)account
                   timeoutInSeconds:(NSTimeInterval)timeoutInSeconds
                uploadProgressBlock:(void(^)(int64_t bytesWritten, int64_t totalBytesWritten, int64_t totalBytesExpectedToWrite))uploadProgressBlock
                        streamBlock:(void(^)(NSObject<STTwitterRequestProtocol> *request, NSData *data))streamBlock
                    completionBlock:(void(^)(NSObject<STTwitterRequestProtocol> *request, NSDictionary *requestHeaders, NSDictionary *responseHeaders, id response))completionBlock
                         errorBlock:(void(^)(NSObject<STTwitterRequestProtocol> *request, NSDictionary *requestHeaders, NSDictionary *responseHeaders, NSError *error))errorBlock;

- (void)startRequest;
- (NSURLRequest *)preparedURLRequest;

@end
