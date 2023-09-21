//
// Created by Diego on 20/09/2023.
//

#ifndef OPENGL_KEYBOARD_H
#define OPENGL_KEYBOARD_H

#include <GLFW/glfw3.h>

class GLFWwindow;

class Keyboard {
public:
    static void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);

    [[nodiscard]] inline static bool keyIsUp(int key) {
        return !currentKeyState[key];
    }
    [[nodiscard]] inline static bool keyWasUp(int key) {
        return !previousKeyState[key];
    }
    [[nodiscard]] inline static bool keyIsDown(int key) {
        return currentKeyState[key];
    }
    [[nodiscard]] inline static bool keyWasDown(int key) {
        return previousKeyState[key];
    }
    [[nodiscard]] inline static bool getIsKeyChanged(int key) {
        return keyIsUp(key) && keyWasDown(key) || keyIsDown(key) && keyWasUp(key);
    }

    static void update();

private:
    static inline bool currentKeyState[GLFW_KEY_LAST];
    static inline bool previousKeyState[GLFW_KEY_LAST];
};


#endif //OPENGL_KEYBOARD_H
