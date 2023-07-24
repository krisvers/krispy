#ifndef KRISPY_PLATFORM_CONSOLE_H
#define KRISPY_PLATFORM_CONSOLE_H

#include <krispy.h>
#include <kplatform.h>

typedef enum KplatformConsoleLevelEnum {
    KPLATFORM_CONSOLE_LEVEL_DEBUG = -1,
    KPLATFORM_CONSOLE_LEVEL_LOG = 0,
    KPLATFORM_CONSOLE_LEVEL_WARN = 1,
    KPLATFORM_CONSOLE_LEVEL_ERROR = 2,
} kplatform_console_level_enum;

u64 kplatform_console_write(kplatform_console_level_enum level, char * buffer, u64 length);
u64 kplatform_console_read(char * buffer, u64 max_length);

#endif
