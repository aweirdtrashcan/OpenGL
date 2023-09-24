//
// Created by diego on 23/09/23.
//

#ifndef OPENGL_CAMERA_H
#define OPENGL_CAMERA_H

#include "includes.h"

enum CameraDirection : uint8_t {
    NONE = 0,
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera {
public:
    Camera(glm::vec3 position);

    void updateCameraDirection(double dx, double dy);
    void updateCameraPosition(CameraDirection direction, double deltaTime);
    void updateCameraZoom(double dy);

    const glm::mat4& getViewMatrix();

private:
    void updateCameraVectors();

private:
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    glm::vec3 cameraRight;
    glm::vec3 worldUp;

    float yaw;
    float pitch;
    float speed;
    float zoom;
};


#endif //OPENGL_CAMERA_H
