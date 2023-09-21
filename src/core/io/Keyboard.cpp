//
// Created by Diego on 20/09/2023.
//

#include "Keyboard.h"

#include <cstring>

void Keyboard::keyCallback(GLFWwindow *window, int key, int scanCode, int action, int mods) {
    switch (action) {
        case GLFW_PRESS: {
            currentKeyState[key] = true;
        } break;
        case GLFW_RELEASE: {
            currentKeyState[key] = false;
        } break;
        case GLFW_REPEAT: {
            currentKeyState[key] = true;
        } break;
        default: break;
    }

}

void Keyboard::update() {
    memcpy(previousKeyState, currentKeyState, GLFW_KEY_LAST);
}
