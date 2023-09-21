//
// Created by Diego on 20/09/2023.
//

#include "Mouse.h"

#include <cstring>

void Mouse::update() {
    memcpy(previousButtonState, currentButtonState, GLFW_MOUSE_BUTTON_LAST);
}
