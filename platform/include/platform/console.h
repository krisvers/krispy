#ifndef KRISPY_PLATFORM_CONSOLE_H
#define KRISPY_PLATFORM_CONSOLE_H

#include <krispy.h>
#include <platform.h>
#include <string.h>

typedef enum PlatformConsoleLevelEnum {
    PLATFORM_CONSOLE_LEVEL_DEBUG = -1,
    PLATFORM_CONSOLE_LEVEL_LOG = 0,
    PLATFORM_CONSOLE_LEVEL_WARN = 1,
    PLATFORM_CONSOLE_LEVEL_ERROR = 2,
} platform_console_level_enum;

u64 platform_console_write(platform_console_level_enum level, char * buffer, u64 length);
u64 platform_console_read(char * buffer, u64 max_length);

#define PLATFORM_CONSOLE_ERROR(message) platform_console_write(PLATFORM_CONSOLE_LEVEL_ERROR, message, strlen(message));
#define PLATFORM_CONSOLE_WARN(message) platform_console_write(PLATFORM_CONSOLE_LEVEL_WARN, message, strlen(message));
#define PLATFORM_CONSOLE_LOG(message) platform_console_write(PLATFORM_CONSOLE_LEVEL_LOG, message, strlen(message));
#define PLATFORM_CONSOLE_DEBUG(message) platform_console_write(PLATFORM_CONSOLE_LEVEL_DEBUG, message, strlen(message));

#endif
