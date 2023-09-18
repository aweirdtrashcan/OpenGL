#include <iostream>

#include "Shader.h"

#include <glad/glad.h>
#include <glad/glad.c>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb_image.h>

static constexpr int HEIGHT = 600;
static constexpr int WIDTH = 800;

static inline void framebuffer_resize_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processKey(GLFWwindow *window);

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_API, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL", nullptr, nullptr);

    if (!window) {
        std::cerr<<"Failed to create GLFW Window.\n";
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr<<"Failed to initialize GLAD.\n";
        return -2;
    }

    glViewport(0, 0, WIDTH, HEIGHT);

    glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);

    //glEnable(GL_DEPTH);

    unsigned int VAO = 0, VBO = 0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    const float vertices[] = {
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
    };

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    Shader shader("../shaders/vertex.glsl", "../shaders/fragment.glsl");

    glm::mat4 mvp(1.0f);

    glm::mat4 view(1.0f);
    glm::mat4 projection(1.0f);
    glm::mat4 model(1.0f);
    glm::mat4 rotation(1.0f);

    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -6.0f)) *
            glm::rotate(rotation, glm::radians(40.f), glm::vec3(0.2f, 1.0f, 0.0f));

    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(45.f), (float) ((float) WIDTH / (float) HEIGHT), 0.1f, 100.f);

    unsigned int tex = 0;

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    struct Image {

        uint32_t id = 0;
        int32_t width = 0;
        int32_t height = 0;
        int32_t nrChannels = 0;
        uint8_t *data = nullptr;
    };

    Image container;

    container.data = stbi_load("assets/container.jpg", &container.width, &container.height, &container.nrChannels, 0);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, container.width, container.height, 0, GL_RGB, GL_UNSIGNED_BYTE, container.data);


    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        processKey(window);

        shader.Use();

        mvp = projection * view * model;

        shader.setMatrix4x4f("m", glm::value_ptr(mvp));

        glClearColor(0.5f, 0.2f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / (5 * sizeof(float)));

        glfwSwapBuffers(window);
    }

    return 0;
}

void processKey(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}