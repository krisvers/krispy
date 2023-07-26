#include <platform.h>

#ifdef KRISPY_PLATFORM_POSIX

#include <krispy.h>
#include <platform/console.h>

#define _POSIX_SOURCE
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

u64 platform_console_write(platform_console_level_enum level, char * buffer, u64 length) {
#ifdef KLOG_CONSOLE
    static const char * escape_colors[4] = { "1;34", "1;32", "1;33", "1;31" };
    printf("\033[%sm", escape_colors[level + 1]);
    fflush(stdout);
    u64 written = (u64) write(STDOUT_FILENO, buffer, length);
    printf("\033[0m");
    fflush(stdout);

    return written;
#else
    return length;
#endif
}

u64 platform_console_read(char * buffer, u64 max_length) {
    char * str = fgets(buffer, max_length, stdin);
    if (str == NULL) {
        return 0;
    }

    return strlen(str);
}

#endif