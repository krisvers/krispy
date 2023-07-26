#ifndef KRISPY_PLATFORM_H
#define KRISPY_PLATFORM_H

#include <krispy.h>

#ifndef KRISPY_PLATFORM_CHOSEN
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN64)
        #define KRISPY_PLATFORM_WINDOWS 1
    #elif defined(__linux__) || defined(__gnu_linux__)
        #define KRISPY_PLATFORM_LINUX 1
        #if defined(__ANDROID__)
            #define KRISPY_PLATFORM_ANDROID 1
        #endif
    #elif defined(__unix__)
        #define KRISPY_PLATFORM_UNIX 1
    #elif defined(_POSIX_VERSION)
        #define KRISPY_PLATFORM_POSIX 1
    #elif __APPLE__
        #define KRISPY_PLATFORM_APPLE 1
        #include <TargetConditionals.h>
        #if TARGET_IPHONE_SIMULATOR
            #define KRISPY_PLATFORM_IOS 1
            #define KRISPY_PLATFORM_IOS_SIMULATOR 1
        #elif TARGET_OS_IPHONE
            #define KRISPY_PLATFORM_IOS 1
        #elif TARGET_OS_MAC
            #define KRISPY_PLATFORM_MAC 1
        #else
            #error "Unknown Apple platform"
        #endif
    #else
        #error "Unknown platform"
    #endif
#endif

#endif
