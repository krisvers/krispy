#ifndef KRISPY_PLATFORM_WINDOW_H
#define KRISPY_PLATFORM_WINDOW_H

#include <krispy.h>
#include <GLFW/glfw3.h>
#include <platform/input.h>

typedef enum PlatformWindowSuccessEnum {
    PLATFORM_WINDOW_UPDATE_ERROR = -2,
    PLATFORM_WINDOW_CREATION_ERROR = -1,
    PLATFORM_WINDOW_SUCCESS = 0,
} platform_window_success_enum;

struct PlatformWindow;
typedef void (*platform_window_key_callback)(struct PlatformWindow * window, keycode_enum key);
typedef void (*platform_window_mouse_pos_callback)(struct PlatformWindow * window, i32 x, i32 y);
typedef void (*platform_window_mouse_button_callback)(struct PlatformWindow * window, mouse_button_enum button);
typedef void (*platform_window_mouse_scroll_callback)(struct PlatformWindow * window, i8 x, i8 y);
typedef void (*platform_window_should_close_callback)(struct PlatformWindow * window);

typedef struct PlatformWindow {
    GLFWwindow * _glfw_window;
    platform_window_key_callback key;
    platform_window_mouse_pos_callback mouse_pos;
    platform_window_mouse_button_callback mouse_button;
    platform_window_mouse_scroll_callback mouse_scroll;
    platform_window_should_close_callback should_close;
} platform_window_t;

platform_window_success_enum platform_window_create(platform_window_t * window, char * title, u32 w, u32 h);
platform_window_success_enum platform_window_destroy(platform_window_t * window);
platform_window_success_enum platform_window_update(platform_window_t * window);

#endif