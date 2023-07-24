#ifndef KRISPY_KPLATFORM_H
#define KRISPY_KPLATFORM_H

#include <krispy.h>

#ifndef KRISPY_KPLATFORM_CHOSEN
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN64)
        #define KRISPY_KPLATFORM_WINDOWS 1
    #elif defined(__linux__) || defined(__gnu_linux__)
        #if defined(__ANDROID__)
            #define KRISPY_KPLATFORM_ANDROID 1
        #endif
    #elif defined(__unix__)
        #define KRISPY_KPLATFORM_UNIX 1
    #elif defined(_POSIX_VERSION)
        #define KRISPY_KPLATFORM_POSIX 1
    #elif __APPLE__
        #define KRISPY_KPLATFORM_APPLE 1
        #include <TargetConditionals.h>
        #if TARGET_IPHONE_SIMULATOR
            #define KRISPY_KPLATFORM_IOS 1
            #define KRISPY_KPLATFORM_IOS_SIMULATOR 1
        #elif TARGET_OS_IPHONE
            #define KRISPY_KPLATFORM_IOS 1
        #elif TARGET_OS_MAC
            #define KRISPY_KPLATFORM_MACOS
        #else
            #error "Unknown Apple platform"
        #endif
    #else
        #error "Unknown platform"
    #endif
#endif

#endif
