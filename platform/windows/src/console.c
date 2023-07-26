#include <platform.h>

#ifdef KRISPY_PLATFORM_WINDOWS

#include <krispy.h>
#include <platform/console.h>

#include <windows.h>
#include <windowsx.h>
#include <winbase.h>

u64 platform_console_write(platform_console_level_enum level, char * buffer, u64 length) {
#ifdef KLOG_CONSOLE
    static u8 levels[4] = { 0x01, 0x02, 0x06, 0x04 };
    DWORD written = 0;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, levels[level + 1]);
    if (WriteConsoleA(console, buffer, length, &written, NULL) == 0) {
        return 0;
    }

    return (u64) written;
#endif

    return length;
}

u64 platform_console_read(char * buffer, u64 max_length) {
    HANDLE console = GetStdHandle(STD_INPUT_HANDLE);
    DWORD written = 0;
    if (ReadConsoleA(console, buffer, max_length, &written, NULL) == 0) {
        return 0;
    }

    return (u64) written;
}

#endif
