#include <platform.h>

#ifdef KRISPY_PLATFORM_LINUX

#include <krispy.h>
#include <platform/singleton.h>
#include <GLFW/glfw3.h>

platform_singleton_success_enum platform_singleton_init(void) {
    if (glfwInit() != GLFW_TRUE) {
        return PLATFORM_SINGLETON_FAILURE_ERROR;
    }

    return PLATFORM_SINGLETON_SUCCESS;
}

platform_singleton_success_enum platform_singleton_deinit(void) {
    glfwTerminate();

    return PLATFORM_SINGLETON_SUCCESS;
}

platform_singleton_success_enum platform_singleton_poll_events(void) {
    glfwPollEvents();

    return PLATFORM_SINGLETON_POLL_ERROR;
}
    
#endif