//
// Created by diego on 23/09/23.
//

#include "Camera.h"

Camera::Camera(glm::vec3 position)
    :
    cameraPos(position),
    cameraFront(0.0f, 0.0f, -1.0f),
    cameraUp(0.0f),
    cameraRight(0.0f),
    worldUp(0.0f, 1.0f, 0.0f),
    yaw(-90.0f),
    pitch(0.0f),
    speed(2.5f),
    zoom(45.0f) {
    updateCameraVectors();
}

void Camera::updateCameraDirection(double dx, double dy) {
    glm::vec3 direction;

}

void Camera::updateCameraPosition(CameraDirection direction, double deltaTime) {

}

void Camera::updateCameraZoom(double dy) {

}

const glm::mat4 &Camera::getViewMatrix() {
    return glm::mat4();
}

void Camera::updateCameraVectors() {

}
