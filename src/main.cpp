#include "core/Shader.h"

#include "includes.h"

#include <glad/glad.h>
#include <glad/glad.c>

#include <GLFW/glfw3.h>

static constexpr int HEIGHT = 600;
static constexpr int WIDTH = 800;

static inline void framebuffer_resize_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processKey(GLFWwindow* window);

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_API, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL", nullptr, nullptr);

    if (!window) {
        std::cerr << "Failed to create GLFW Window.\n";
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD.\n";
        return -2;
    }

    glViewport(0, 0, WIDTH, HEIGHT);

    glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);

    //glEnable(GL_DEPTH);

    unsigned int VAO = 0, VBO = 0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    struct vertex {
        struct {
            float x = 0;
            float y = 0;
            float z = 0;
        } pos;

        struct {
            float u = 0;
            float v = 0;
        } texCoord;
    };

    const vertex vertices[] = {
            {-0.5f, -0.5f, -0.5f, 0.0f, 0.0f},
            {0.5f, -0.5f, -0.5f, 1.0f, 0.0f},
            {0.5f, 0.5f, -0.5f, 1.0f, 1.0f},
            {0.5f, 0.5f, -0.5f, 1.0f, 1.0f},
            {-0.5f, 0.5f, -0.5f, 0.0f, 1.0f},
            {-0.5f, -0.5f, -0.5f, 0.0f, 0.0f},

            {-0.5f, -0.5f, 0.5f, 0.0f, 0.0f},
            {0.5f, -0.5f, 0.5f, 1.0f, 0.0f},
            {0.5f, 0.5f, 0.5f, 1.0f, 1.0f},
            {0.5f, 0.5f, 0.5f, 1.0f, 1.0f},
            {-0.5f, 0.5f, 0.5f, 0.0f, 1.0f},
            {-0.5f, -0.5f, 0.5f, 0.0f, 0.0f},

            {-0.5f, 0.5f, 0.5f, 1.0f, 0.0f},
            {-0.5f, 0.5f, -0.5f, 1.0f, 1.0f},
            {-0.5f, -0.5f, -0.5f, 0.0f, 1.0f},
            {-0.5f, -0.5f, -0.5f, 0.0f, 1.0f},
            {-0.5f, -0.5f, 0.5f, 0.0f, 0.0f},
            {-0.5f, 0.5f, 0.5f, 1.0f, 0.0f},

            {0.5f, 0.5f, 0.5f, 1.0f, 0.0f},
            {0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
            {0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
            {0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
            {0.5f, -0.5f,  0.5f,  0.0f, 0.0f},
            {0.5f,  0.5f,  0.5f,  1.0f, 0.0f},

            {-0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
            {0.5f, -0.5f, -0.5f,  1.0f, 1.0f},
            {0.5f, -0.5f,  0.5f,  1.0f, 0.0f},
            {0.5f, -0.5f,  0.5f,  1.0f, 0.0f},
            {-0.5f, -0.5f,  0.5f,  0.0f, 0.0f},
            {-0.5f, -0.5f, -0.5f,  0.0f, 1.0f},

            {-0.5f,  0.5f, -0.5f,  0.0f, 1.0f},
            {0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
            {0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
            {0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
            {-0.5f,  0.5f,  0.5f,  0.0f, 0.0f},
            {-0.5f,  0.5f, -0.5f,  0.0f, 1.0f}
    };

//    const float vertices[] = {
//            0.0f, 0.5f, 0.0f, 0.0f, 0.0f,
//            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
//            0.5f, -0.5f, 0.0f, 0.0f, 0.0f
//    };

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    Shader shader("../src/shaders/vertex.glsl", "../src/shaders/fragment.glsl");

    glm::mat4 mvp(1.0f);

    glm::mat4 view(1.0f);
    glm::mat4 projection(1.0f);
    glm::mat4 model(1.0f);

    model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
    view = glm::translate(view, glm::vec3(-3.0f, 0.0f, 0.0f));
    projection = glm::perspective(glm::radians(45.f), (float)((float)WIDTH / (float)HEIGHT), 0.1f, 100.f);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        processKey(window);

        shader.Use();
        shader.setMatrix("matrix", glm::value_ptr(mvp));

        glClearColor(0.5f, 0.2f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        static constexpr int size = (int)std::size(vertices);
        glDrawArrays(GL_TRIANGLES, 0, size);

        glfwSwapBuffers(window);
    }

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glfwTerminate();

    return 0;
}

void processKey(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}