//
// Created by Diego on 16/09/2023.
//

#include "Shader.h"

#include "Utils.h"

#include <glad/glad.h>

#include <fstream>
#include <iostream>

Shader::Shader(const char *vertexPath, const char *fragmentPath) {
    std::string stdbuf = readShaderFile(vertexPath);
    const char *code = stdbuf.c_str();

    unsigned int vertShader = 0, fragShader = 0;

    vertShader = glCreateShader(GL_VERTEX_SHADER);
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    ID = glCreateProgram();

    glShaderSource(vertShader, 1, &code, nullptr);
    glCompileShader(vertShader);
    if (!checkGlError(vertShader, Shader::GlStatus::SHADER_COMPILE)) {
        _break();
    }

    stdbuf.clear();
    code = nullptr;

    stdbuf = readShaderFile(fragmentPath);
    code = stdbuf.c_str();

    glShaderSource(fragShader, 1, &code, nullptr);
    glCompileShader(fragShader);
    if (!checkGlError(fragShader, Shader::GlStatus::SHADER_COMPILE)) {
        _break();
    }

    glUseProgram(ID);
    glAttachShader(ID, vertShader);
    glAttachShader(ID, fragShader);
    glLinkProgram(ID);
    if (!checkGlError(ID, Shader::GlStatus::PROGRAM_LINK)) {
        _break();
    }

    std::cout << "Shader created successfully!\n";
}

Shader::~Shader() {
    std::cout << "Deleting Shader...\n";
    glDeleteProgram(ID);
}

void Shader::setInt(const char *uniformName, int value) const {
    glUniform1i(glGetUniformLocation(ID, uniformName), value);
}

void Shader::setFloat(const char *uniformName, float value) const {
    glUniform1f(glGetUniformLocation(ID, uniformName), value);
}

void Shader::setMatrix4x4f(const char *uniformName, const float *matrix_ptr) {
    glUniformMatrix4fv(glGetUniformLocation(ID, uniformName), 1, GL_FALSE, matrix_ptr);
}

std::string Shader::readShaderFile(const char *path) {
    std::ifstream file(path, std::ios::ate);

    if (!file.is_open()) {
        std::cerr << "Failed to open shader file " << path << "\n";
        _break();
    }

    std::streamsize size = file.tellg();

    file.seekg(0);

    std::string buffer(size, '\0');

    file.read(&buffer[0], size);

    file.close();

    return buffer;
}

bool Shader::checkGlError(unsigned int id, Shader::GlStatus status) {
    char infoLog[512];
    GLint success = 0;

    switch (status) {
        case Shader::GlStatus::PROGRAM_LINK: {
            glGetProgramiv(id, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(id, 512, nullptr, infoLog);
                std::cerr << "*** [OpenGL Link Failure] ***:\n" << infoLog << "\n";
                return false;
            }
        }
        case Shader::GlStatus::SHADER_COMPILE: {
            glGetShaderiv(id, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(id, 512, nullptr, infoLog);
                std::cerr << "*** [OpenGL Compile Failure] ***:\n" << infoLog << "\n";
                return false;
            }
        }
        default: return true;
    }

    return true;
}

void Shader::Use() const {
    glUseProgram(ID);
}
