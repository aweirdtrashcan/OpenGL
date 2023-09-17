//
// Created by Diego on 16/09/2023.
//

#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

#include <string>

class Shader {
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void setInt(const char* uniformName, int value) const;
    void setFloat(const char* uniformName, float value) const;
    void setMatrix4x4f(const char* uniformName, const float* matrix_ptr);

    void Use() const;

private:
    static std::string readShaderFile(const char* path);

    enum class GlStatus {
        SHADER_COMPILE,
        PROGRAM_LINK
    };

    static bool checkGlError(unsigned int id, Shader::GlStatus status);

private:
    unsigned int ID = 0;
};


#endif //OPENGL_SHADER_H
