#include "core/Shader.h"

#include "includes.h"

#include <glad/glad.h>
#include <glad/glad.c>

#include <GLFW/glfw3.h>

#include "core/io/Keyboard.h"
#include "core/io/Mouse.h"
#include "core/Image.h"
#include "core/Texture.h"

static inline void framebuffer_resize_callback(GLFWwindow* window, int width, int height);

void processKey(GLFWwindow* window);

void processObjectMovement(glm::vec3 &objPos);
void processObjectScale(glm::vec3 &objScale);
void shouldReset(glm::vec3 &objPos, glm::vec3 &objScale);

static int height = 600;
static int width = 800;
static double deltaTime;

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

static const vertex vertices[] = {
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

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_API, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(width, height, "OpenGL", nullptr, nullptr);

    if (!window) {
        std::cerr << "Failed to create GLFW Window.\n";
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD.\n";
        return -2;
    }

    glViewport(0, 0, width, height);

    glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);

    glfwSetKeyCallback(window, Keyboard::keyCallback);
    glfwSetMouseButtonCallback(window, Mouse::mouseButtonCallback);
    glfwSetCursorPosCallback(window, Mouse::cursorPosCallback);
    glfwSetScrollCallback(window, Mouse::mouseWheelCallback);

    unsigned int VAO = 0, VBO = 0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    Shader shader("../src/shaders/vertex.glsl", "../src/shaders/fragment.glsl");
    Image container("../assets/awesomeface.png");
    Texture tex(container, Texture::Type::TYPE_2D, Texture::Format::RGBA, 0);

    glfwSwapInterval(0);

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) {
        static double startTime = 0.0f;
        static double lastSecond;
        static int frameCount;

        frameCount++;
        deltaTime = glfwGetTime() - startTime;
        startTime = glfwGetTime();

        processKey(window);

        if ((glfwGetTime() - lastSecond) >= 1.0) {
            std::cout << "FPS: " << frameCount << "\n";
            frameCount = 0;
            lastSecond = glfwGetTime();
        }

        shader.Use();
        tex.bind();

        glm::mat4 view(1.0f);
        glm::mat4 projection(1.0f);
        glm::mat4 model(1.0f);
        static glm::vec3 cameraPosition(0.0f);
        static glm::vec3 objectPosition(0.0f, 0.0f, -5.0f);
        static glm::vec3 objectScale(1.0f);
        processObjectMovement(objectPosition);
        processObjectScale(objectScale);
        shouldReset(objectPosition, objectScale);


        // Order of models: Scale -> Rotation -> Translation
        // Order of MVP: Projection -> View -> Model
        // In practice, you multiply in reverse order.

        model = glm::translate(model, glm::vec3(objectPosition.x, objectPosition.y, objectPosition.z));
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(-55.f), glm::vec3(0.5f, 1.0f, 0.0f));
        model = glm::scale(model, objectScale);

        view = glm::translate(view, cameraPosition);

        projection = glm::perspective(glm::radians(45.f), (float)((float)width / (float)height), 0.1f, 100.f);

        glm::mat4 mvp = projection * view * model;

        shader.setMatrix("matrix", glm::value_ptr(mvp));

        glClearColor(0.5f, 0.2f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        static constexpr int size = (int)std::size(vertices);
        glDrawArrays(GL_TRIANGLES, 0, size);

        glfwSwapBuffers(window);

        Keyboard::update();
        Mouse::update();

        glfwPollEvents();
    }

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void processKey(GLFWwindow* window) {

    if (Keyboard::keyIsDown(GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, true);
    }

    if (Keyboard::keyIsDown(GLFW_KEY_V) && Keyboard::keyWasUp(GLFW_KEY_V)) {
        static bool vSync = false;
        vSync = !vSync;
        if (vSync) {
            std::cout << "vSync enabled!\n";
        } else {
            std::cout << "vSync disabled!\n";
        }
        glfwSwapInterval(vSync);
    }
}

void processObjectMovement(glm::vec3 &objPos) {
    if (Keyboard::keyIsDown(GLFW_KEY_A)) {
        objPos.x -= 1.0f * (float)deltaTime;
    }

    if (Keyboard::keyIsDown(GLFW_KEY_D)) {
        objPos.x += 1.0f * (float)deltaTime;
    }

    if (Keyboard::keyIsDown(GLFW_KEY_W)) {
        objPos.y += 1.0f * (float)deltaTime;
    }

    if (Keyboard::keyIsDown(GLFW_KEY_S)) {
        objPos.y -= 1.0f * (float)deltaTime;
    }
}

void processObjectScale(glm::vec3 &objScale) {
    if (Keyboard::keyIsDown(GLFW_KEY_LEFT)) {
        objScale.x -= 1.0f * (float)deltaTime;
    }

    if (Keyboard::keyIsDown(GLFW_KEY_RIGHT)) {
        objScale.x += 1.0f * (float)deltaTime;
    }

    if (Keyboard::keyIsDown(GLFW_KEY_UP)) {
        objScale.y += 1.0f * (float)deltaTime;
    }

    if (Keyboard::keyIsDown(GLFW_KEY_DOWN)) {
        objScale.y -= 1.0f * (float)deltaTime;
    }
}

void shouldReset(glm::vec3 &objPos, glm::vec3 &objScale) {
    if (Keyboard::keyIsDown(GLFW_KEY_C) && Keyboard::keyWasUp(GLFW_KEY_C)) {
        objPos = glm::vec3(0.0f, 0.0f, -5.0f);
        objScale = glm::vec3(1.0f);
    }
}

void framebuffer_resize_callback(GLFWwindow* window, int w, int h) {
    glViewport(0, 0, w, h);
    width = w;
    height = h;
}