//
// Created by Diego on 20/09/2023.
//

#ifndef OPENGL_MOUSE_H
#define OPENGL_MOUSE_H

#include <GLFW/glfw3.h>

class Mouse {
public:
    static void cursorPosCallback(GLFWwindow* window, double X, double Y) {
        m_MouseY = Y;
        m_MouseX = X;
    }
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
        switch (action) {
            case GLFW_PRESS: {
                currentButtonState[button] = true;
            } break;
            case GLFW_REPEAT: {
                currentButtonState[button] = true;
            } break;
            case GLFW_RELEASE: {
                currentButtonState[button] = false;
            } break;
            default: break;
        }
    }
    static void mouseWheelCallback(GLFWwindow* window, double dx, double dy) {
        m_WheelDX = dx;
        m_WheelDY = dy;
    }

    static double getMouseX() {
        return m_MouseX;
    }
    static double getMouseY() {
        return m_MouseY;
    }

    static double getScrollDX() {
        double mx = m_WheelDX;
        m_WheelDX = 0;
        return mx;
    }
    static double getScrollDY() {
        double my = m_WheelDY;
        my = 0;
        return my;
    }

    [[nodiscard]] inline static bool buttonIsUp(int button) {
        return !currentButtonState[button];
    }
    [[nodiscard]] inline static bool buttonWasUp(int button) {
        return !previousButtonState[button];
    }
    [[nodiscard]] inline static bool buttonIsDown(int button) {
        return currentButtonState[button];
    }
    [[nodiscard]] inline static bool buttonWasDown(int button) {
        return previousButtonState[button];
    }

    static void update();

private:
    inline static double m_MouseX, m_MouseY;
    inline static double m_WheelDX, m_WheelDY;

    inline static bool currentButtonState[GLFW_MOUSE_BUTTON_LAST];
    inline static bool previousButtonState[GLFW_MOUSE_BUTTON_LAST];
};


#endif //OPENGL_MOUSE_H
