#include <platform.h>

#ifdef KRISPY_PLATFORM_MAC

#include <krispy.h>
#include <platform/console.h>
#include <platform/window.h>
#include <platform/input.h>
#include <GLFW/glfw3.h>

static void internal_glfw_window_key_fun(GLFWwindow * glfw_win, int key, int scancode, int action, int mod);
static void internal_glfw_window_mouse_pos_fun(GLFWwindow * glfw_win, f64 x, f64 y);
static void internal_glfw_window_mouse_button_fun(GLFWwindow * glfw_win, int button, int action, int mod);
static void internal_glfw_window_mouse_scroll_fun(GLFWwindow * glfw_win, f64 x, f64 y);
static void internal_glfw_window_should_close_fun(GLFWwindow * glfw_win);

platform_window_success_enum platform_window_create(platform_window_t * window, char * title, u32 w, u32 h) {
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow * glfw_win = glfwCreateWindow(w, h, title, NULL, NULL);
    if (glfw_win == NULL) {
        return PLATFORM_WINDOW_CREATION_ERROR;
    }

    glfwMakeContextCurrent(glfw_win);
    glfwSetWindowUserPointer(glfw_win, window);
    glfwSetKeyCallback(glfw_win, internal_glfw_window_key_fun);
    glfwSetCursorPosCallback(glfw_win, internal_glfw_window_mouse_pos_fun);
    glfwSetMouseButtonCallback(glfw_win, internal_glfw_window_mouse_button_fun);
    glfwSetScrollCallback(glfw_win, internal_glfw_window_mouse_scroll_fun);
    glfwSetWindowCloseCallback(glfw_win, internal_glfw_window_should_close_fun);

    window->_glfw_window = glfw_win;
    window->key = NULL;
    window->mouse_pos = NULL;
    window->mouse_button = NULL;
    window->mouse_scroll = NULL;
    window->should_close = NULL;

    return PLATFORM_WINDOW_SUCCESS;
}

platform_window_success_enum platform_window_destroy(platform_window_t * window) {
    glfwDestroyWindow(window->_glfw_window);

    return PLATFORM_WINDOW_SUCCESS;
}

platform_window_success_enum platform_window_update(platform_window_t * window) {
    glfwSwapBuffers(window->_glfw_window);

    return PLATFORM_WINDOW_SUCCESS;
}

#define KEYCODE_MAP_GLFW_KEY(key, keycode) case GLFW_KEY_##key: return KEYCODE_##keycode;
#define KEYCODE_MAP_GLFW_KEY_SAME_NAME(key) KEYCODE_MAP_GLFW_KEY(key, key)

static keycode_enum glfw_key_map(int key) {
    switch (key) {
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(UNKNOWN);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(SPACE);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(APOSTROPHE);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(COMMA);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(MINUS);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(PERIOD);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(SLASH);

        KEYCODE_MAP_GLFW_KEY_SAME_NAME(0);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(1);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(2);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(3);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(4);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(5);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(6);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(7);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(8);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(9);

        KEYCODE_MAP_GLFW_KEY_SAME_NAME(SEMICOLON);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(EQUAL);

        KEYCODE_MAP_GLFW_KEY_SAME_NAME(A);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(B);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(C);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(D);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(E);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(F);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(G);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(H);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(I);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(J);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(K);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(L);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(M);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(N);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(O);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(P);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(Q);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(R);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(S);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(T);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(U);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(V);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(W);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(X);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(Y);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(Z);

        KEYCODE_MAP_GLFW_KEY(LEFT_BRACKET, LBRACK);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(BACKSLASH);
        KEYCODE_MAP_GLFW_KEY(RIGHT_BRACKET, RBRACK);
        KEYCODE_MAP_GLFW_KEY(GRAVE_ACCENT, GRAVE);

        KEYCODE_MAP_GLFW_KEY(WORLD_1, UNKNOWN);
        KEYCODE_MAP_GLFW_KEY(WORLD_2, UNKNOWN);

        KEYCODE_MAP_GLFW_KEY_SAME_NAME(ESCAPE);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(ENTER);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(TAB);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(BACKSPACE);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(INSERT);

        // manual intervention
        // DELETE is a macro defined in <winnt.h> on Windows
        // this reduces name collision
    case GLFW_KEY_DELETE: return KEYCODE_DEL;

        KEYCODE_MAP_GLFW_KEY_SAME_NAME(RIGHT);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(LEFT);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(UP);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(DOWN);

        KEYCODE_MAP_GLFW_KEY(PAGE_UP, PGUP);
        KEYCODE_MAP_GLFW_KEY(PAGE_DOWN, PGDN);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(HOME);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(END);

        KEYCODE_MAP_GLFW_KEY(CAPS_LOCK, CAPS);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(SCROLL_LOCK);
        KEYCODE_MAP_GLFW_KEY(PRINT_SCREEN, PRTSCR);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(PAUSE);

        KEYCODE_MAP_GLFW_KEY_SAME_NAME(F1);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(F2);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(F3);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(F4);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(F5);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(F6);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(F7);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(F8);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(F9);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(F10);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(F11);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(F12);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(F13);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(F14);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(F15);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(F16);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(F17);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(F18);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(F19);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(F20);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(F21);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(F22);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(F23);
        KEYCODE_MAP_GLFW_KEY_SAME_NAME(F24);

        KEYCODE_MAP_GLFW_KEY(KP_0, NUMPAD_0);
        KEYCODE_MAP_GLFW_KEY(KP_1, NUMPAD_1);
        KEYCODE_MAP_GLFW_KEY(KP_2, NUMPAD_2);
        KEYCODE_MAP_GLFW_KEY(KP_3, NUMPAD_3);
        KEYCODE_MAP_GLFW_KEY(KP_4, NUMPAD_4);
        KEYCODE_MAP_GLFW_KEY(KP_5, NUMPAD_5);
        KEYCODE_MAP_GLFW_KEY(KP_6, NUMPAD_6);
        KEYCODE_MAP_GLFW_KEY(KP_7, NUMPAD_7);
        KEYCODE_MAP_GLFW_KEY(KP_8, NUMPAD_8);
        KEYCODE_MAP_GLFW_KEY(KP_9, NUMPAD_9);
        KEYCODE_MAP_GLFW_KEY(KP_DECIMAL, NUMPAD_DECIMAL);
        KEYCODE_MAP_GLFW_KEY(KP_DIVIDE, NUMPAD_DIVIDE);
        KEYCODE_MAP_GLFW_KEY(KP_MULTIPLY, NUMPAD_MULTIPLY);
        KEYCODE_MAP_GLFW_KEY(KP_SUBTRACT, NUMPAD_SUBTRACT);
        KEYCODE_MAP_GLFW_KEY(KP_ADD, NUMPAD_ADD);
        KEYCODE_MAP_GLFW_KEY(KP_ENTER, NUMPAD_ENTER);
        KEYCODE_MAP_GLFW_KEY(KP_EQUAL, NUMPAD_EQUAL);

        KEYCODE_MAP_GLFW_KEY(LEFT_SHIFT, LSHIFT);
        KEYCODE_MAP_GLFW_KEY(LEFT_CONTROL, LCONTROL);
        KEYCODE_MAP_GLFW_KEY(LEFT_ALT, LALT);
        KEYCODE_MAP_GLFW_KEY(LEFT_SUPER, LSUPER);
        KEYCODE_MAP_GLFW_KEY(RIGHT_SHIFT, RSHIFT);
        KEYCODE_MAP_GLFW_KEY(RIGHT_CONTROL, RCONTROL);
        KEYCODE_MAP_GLFW_KEY(RIGHT_ALT, RALT);
        KEYCODE_MAP_GLFW_KEY(RIGHT_SUPER, RSUPER);

    default: return KEYCODE_UNKNOWN;
    }
}

static void internal_glfw_window_key_fun(GLFWwindow * glfw_win, int key, int scancode, int action, int mod) {
    platform_window_t * window = glfwGetWindowUserPointer(glfw_win);
    if (window == NULL) {
        return;
    }
    if (window->key == NULL) {
        return;
    }

    window->key(window, glfw_key_map(key));
}

static void internal_glfw_window_mouse_pos_fun(GLFWwindow * glfw_win, f64 x, f64 y) {
    platform_window_t * window = glfwGetWindowUserPointer(glfw_win);
    if (window == NULL) {
        return;
    }
    if (window->mouse_pos == NULL) {
        return;
    }

    window->mouse_pos(window, (i32) x, (i32) y);
}

#define MOUSE_BUTTON_MAP_GLFW_MOUSE_BUTTON(button, buttoncode) case GLFW_MOUSE_BUTTON_##button: return MOUSE_BUTTON_##buttoncode;
#define MOUSE_BUTTON_MAP_GLFW_MOUSE_BUTTON_SAME_NAME(button) MOUSE_BUTTON_MAP_GLFW_MOUSE_BUTTON(button, button)

static mouse_button_enum glfw_mouse_button_map(int button) {
    switch (button) {
        MOUSE_BUTTON_MAP_GLFW_MOUSE_BUTTON(1, 0);
        MOUSE_BUTTON_MAP_GLFW_MOUSE_BUTTON(2, 1);
        MOUSE_BUTTON_MAP_GLFW_MOUSE_BUTTON(3, 2);

    default: return MOUSE_BUTTON_UNKNOWN;
    }
}

static void internal_glfw_window_mouse_button_fun(GLFWwindow * glfw_win, int button, int action, int mod) {
    platform_window_t * window = glfwGetWindowUserPointer(glfw_win);
    if (window == NULL) {
        return;
    }
    if (window->mouse_button == NULL) {
        return;
    }

    window->mouse_button(window, glfw_mouse_button_map(button));
}

static void internal_glfw_window_mouse_scroll_fun(GLFWwindow * glfw_win, f64 x, f64 y) {
    platform_window_t * window = glfwGetWindowUserPointer(glfw_win);
    if (window == NULL) {
        return;
    }
    if (window->mouse_scroll == NULL) {
        return;
    }

    window->mouse_scroll(window, (i8) -x, (i8) y);
}

static void internal_glfw_window_should_close_fun(GLFWwindow * glfw_win) {
    platform_window_t * window = glfwGetWindowUserPointer(glfw_win);
    if (window == NULL) {
        return;
    }
    if (window->should_close == NULL) {
        return;
    }

    window->should_close(window);
}

#endif