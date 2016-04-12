

#import <Foundation/Foundation.h>

extern NSUInteger const kSTHTTPRequestCancellationError;
extern NSUInteger const kSTHTTPRequestDefaultTimeout;

@class STHTTPRequest;

typedef void (^sendRequestBlock_t)(STHTTPRequest *request);
typedef void (^uploadProgressBlock_t)(int64_t bytesWritten, int64_t totalBytesWritten, int64_t totalBytesExpectedToWrite);
typedef void (^downloadProgressBlock_t)(NSData *data, int64_t totalBytesReceived, int64_t totalBytesExpectedToReceive);
typedef void (^completionBlock_t)(NSDictionary *headers, NSString *body);
typedef void (^completionDataBlock_t)(NSDictionary *headers, NSData *body);
typedef void (^errorBlock_t)(NSError *error);

typedef NS_ENUM(NSUInteger, STHTTPRequestCookiesStorage) {
    STHTTPRequestCookiesStorageShared = 0,
    STHTTPRequestCookiesStorageLocal = 1,
    STHTTPRequestCookiesStorageNoStorage = 2,
    STHTTPRequestCookiesStorageUndefined = NSUIntegerMax
};

@interface STHTTPRequest : NSObject <NSURLSessionDataDelegate>

@property (copy) uploadProgressBlock_t uploadProgressBlock;
@property (copy) downloadProgressBlock_t downloadProgressBlock;
@property (copy) completionBlock_t completionBlock;
@property (copy) errorBlock_t errorBlock;
@property (copy) completionDataBlock_t completionDataBlock;

// request
@property (nonatomic, strong) NSString *HTTPMethod; // default: GET, overridden by POST if POSTDictionary or files to upload
@property (nonatomic, strong) NSMutableDictionary *requestHeaders;
@property (nonatomic, strong) NSDictionary *POSTDictionary; // keys and values are NSString instances
@property (nonatomic, strong) NSDictionary *GETDictionary; // appended to the URL string
@property (nonatomic, strong) NSData *rawPOSTData; // eg. to post JSON contents
@property (nonatomic) NSStringEncoding POSTDataEncoding;
@property (nonatomic) NSTimeInterval timeoutSeconds; // ignored if 0
@property (nonatomic) BOOL addCredentialsToURL; // default NO
@property (nonatomic) BOOL encodePOSTDictionary; // default YES
@property (nonatomic) BOOL encodeGETDictionary; // default YES, set to NO if the parameters are already URL encoded
@property (nonatomic, strong, readonly) NSURL *url;
@property (nonatomic) BOOL preventRedirections;
@property (nonatomic) STHTTPRequestCookiesStorage cookieStoragePolicyForInstance; // overrides globalCookiesStoragePolicy

+ (void)setBackgroundCompletionHandler:(void(^)())completionHandler forSessionIdentifier:(NSString *)sessionIdentifier;
//+ (void(^)())backgroundCompletionHandlerForSessionIdentifier:(NSString *)sessionIdentifier;

// response
@property (nonatomic) NSStringEncoding forcedResponseEncoding;
@property (nonatomic, readonly) NSInteger responseStatus;
@property (nonatomic, strong, readonly) NSString *responseStringEncodingName;
@property (nonatomic, strong, readonly) NSDictionary *responseHeaders;
@property (nonatomic, strong) NSString *responseString;
@property (nonatomic, strong, readonly) NSMutableData *responseData;
@property (nonatomic, strong, readonly) NSError *error;
@property (nonatomic) long long responseExpectedContentLength; // set by connection:didReceiveResponse: delegate method; web server must send the Content-Length header for accurate value

// cache
@property (nonatomic) BOOL ignoreCache; // requests ignore cached responses and responses don't get cached

+ (instancetype)requestWithURL:(NSURL *)url;
+ (instancetype)requestWithURLString:(NSString *)urlString;

+ (void)setGlobalIgnoreCache:(BOOL)ignoreCache; // no cache at all when set, overrides the ignoreCache property

- (NSString *)debugDescription; // logged when launched with -STHTTPRequestShowDebugDescription 1
- (NSString *)curlDescription; // logged when launched with -STHTTPRequestShowCurlDescription 1

- (NSString *)startSynchronousWithError:(NSError **)error;
- (void)startAsynchronous;
- (void)cancel;

// Cookies
+ (void)addCookieToSharedCookiesStorage:(NSHTTPCookie *)cookie;
+ (void)addCookieToSharedCookiesStorageWithName:(NSString *)name value:(NSString *)value url:(NSURL *)url;
- (void)addCookieWithName:(NSString *)name value:(NSString *)value url:(NSURL *)url;
- (void)addCookieWithName:(NSString *)name value:(NSString *)value;
- (NSArray *)requestCookies;
- (NSArray *)sessionCookies;
+ (NSArray *)sessionCookiesInSharedCookiesStorage;
+ (void)deleteAllCookiesFromSharedCookieStorage;
+ (void)deleteAllCookiesFromLocalCookieStorage;
- (void)deleteSessionCookies; // empty the cookie storage that is used
+ (void)setGlobalCookiesStoragePolicy:(STHTTPRequestCookiesStorage)cookieStoragePolicy;

// Credentials
+ (NSURLCredential *)sessionAuthenticationCredentialsForURL:(NSURL *)requestURL;
- (void)setUsername:(NSString *)username password:(NSString *)password;
- (NSString *)username;
- (NSString *)password;
+ (void)deleteAllCredentials;

// Headers
- (void)setHeaderWithName:(NSString *)name value:(NSString *)value;
- (void)removeHeaderWithName:(NSString *)name;
- (NSDictionary *)responseHeaders;

// Upload
- (void)addFileToUpload:(NSString *)path parameterName:(NSString *)param;
- (void)addDataToUpload:(NSData *)data parameterName:(NSString *)param;
- (void)addDataToUpload:(NSData *)data parameterName:(NSString *)param mimeType:(NSString *)mimeType fileName:(NSString *)fileName;

// Session
+ (void)clearSession; // delete all credentials and cookies

// DEBUG
- (NSURLRequest *)prepareURLRequest; // prepare the request according to the STHTTPRequest instance state

@end

@interface NSError (STHTTPRequest)
- (BOOL)st_isAuthenticationError;
- (BOOL)st_isCancellationError;
@end

@interface NSString (RFC3986)
- (NSString *)st_stringByAddingRFC3986PercentEscapesUsingEncoding:(NSStringEncoding)encoding;
@end

@interface NSString (STUtilities)
- (NSString *)st_stringByAppendingGETParameters:(NSDictionary *)parameters doApplyURLEncoding:(BOOL)doApplyURLEncoding;
@end
