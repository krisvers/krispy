#ifndef KRISPY_PLATFORM_SINGLETON_H
#define KRISPY_PLATFORM_SINGLETON_H

#include <krispy.h>

typedef enum PlatformSingletonSuccessEnum {
    PLATFORM_SINGLETON_POLL_ERROR = -2,
    PLATFORM_SINGLETON_FAILURE_ERROR = -1,
    PLATFORM_SINGLETON_SUCCESS = 0,
} platform_singleton_success_enum;

platform_singleton_success_enum platform_singleton_init(void);
platform_singleton_success_enum platform_singleton_deinit(void);
platform_singleton_success_enum platform_singleton_poll_events(void);

#endif