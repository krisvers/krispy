#include <krispy.h>
#include <platform/file.h>
#include <platform/console.h>
#include <platform/singleton.h>
#include <platform/window.h>
#include <renderer/frontend.h>
#include <scene/scene.h>


b8 running = TRUE;

void key(platform_window_t * window, keycode_enum key) {
    if (key == KEYCODE_ESCAPE) {
        running = FALSE;
    }
}

void should_close(platform_window_t * window) {
    running = FALSE;
}

int main(void) {
    scene_t scene;
    if (platform_singleton_init() < PLATFORM_SINGLETON_SUCCESS) {
        PLATFORM_CONSOLE_ERROR("Failed to initialize singleton\n");
        return -1;
    }

    platform_window_t window;
    if (platform_window_create(&window, "test", 800, 600) < PLATFORM_WINDOW_SUCCESS) {
        PLATFORM_CONSOLE_ERROR("Failed to create platform window\n");
        goto deinit;
    }

    window.key = key;
    window.should_close = should_close;

    while (running) {
        platform_singleton_poll_events();
    }

    if (platform_window_destroy(&window) < PLATFORM_WINDOW_SUCCESS) {
        PLATFORM_CONSOLE_ERROR("Failed to destroy platform window\n");
    }

deinit:
    if (platform_singleton_deinit() < PLATFORM_SINGLETON_SUCCESS) {
        PLATFORM_CONSOLE_ERROR("Failed to deinitialize singleton\n");
        return -2;
    }

    return 0;
}
