//
// Created by Diego on 25/09/2023.
//

#ifndef OPENGL_CAMERA_H
#define OPENGL_CAMERA_H

#include "includes.h"

enum CameraMovement : char8_t {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera {
public:
    Camera(glm::vec3 position, glm::vec3 up, glm::vec3 yaw);
    glm::mat4& getViewMatrix() {
        lookAt = glm::lookAt(position, position + front, up);
        return lookAt;
    }

    inline void processKeyboard(CameraMovement direction, float deltaTime) {
        float velocity = speed * deltaTime;
        if (direction == FORWARD)
            position += right * velocity;
        if (direction == BACKWARD)
            position -= right * velocity;
        if (direction == LEFT)
            position -= right * velocity;
        if (direction == RIGHT)
            position += right * velocity;
    }

    inline void processMouseMovement(float x, float y, bool constraintPitch = true) {
        x *= sensitivity;
        y *= sensitivity;

        yaw += x;
        pitch += y;

        if (constraintPitch) {
            if (pitch > 89.0f) {
                pitch = 89.0f;
            }
            if (pitch < -90.f) {
                pitch = -90.f;
            }
        }
        updateCameraVector();
    }

    inline void processMouseScroll(float y) {
        zoom -= y;
        if (zoom < 1.0f) {
            zoom = 1.0f;
        } else if (zoom > 120.f) {
            zoom = 120.f;
        }
    }
private:
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 front = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    float yaw = -90.f;
    float pitch = 0.0f;
    float speed = 2.5f;
    float sensitivity = 0.1f;
    float zoom = 45.f;

    glm::mat4 lookAt = glm::mat4(1.0f);

    inline void updateCameraVector() {
        const float pitchRad = glm::radians(pitch);
        const float yawRad = glm::radians(yaw);

        const float cosOfPitch = cosf(pitchRad);
        const float cosOfYaw = cosf(yawRad);
        const float sinOfPitch = sinf(pitchRad);
        const float sinOfYaw = sinf(yawRad);
        front.x = cosOfYaw * cosOfPitch;
        front.y = sinOfPitch;
        front.z = sinOfYaw * cosOfPitch;
        front = glm::normalize(front);

        right = glm::normalize(glm::cross(front, worldUp));
        up = glm::normalize(glm::cross(right, front));
    }
};


#endif //OPENGL_CAMERA_H
