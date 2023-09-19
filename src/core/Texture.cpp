//
// Created by diego on 19/09/23.
//

#include "Texture.h"

#include "includes.h"

#include <glad/glad.h>

Texture::Texture(const Image& image, Texture::Type type, Texture::Format format) {
    glGenTextures(1, &id);

    GLint glFormat = format == Format::RGB ? GL_RGB : GL_RGBA;

    switch (type) {
        case Type::TYPE_1D: {
            glTextureType = GL_TEXTURE_1D;
            glBindTexture(glTextureType, id);
            glTexImage1D(glTextureType,
                         0,
                         GL_RGB,
                         image.getWidth(),
                         0,
                         glFormat,
                         GL_UNSIGNED_BYTE,
                         image.getConstHandle());
            glGenerateMipmap(glTextureType);
            glBindTexture(glTextureType, 0);
        } break;
        case Type::TYPE_1D_ARRAY: { break; }
        case Type::TYPE_2D: {
            glBindTexture(glTextureType, id);
            glTexImage2D(glTextureType,
                         0,
                         GL_RGB,
                         image.getWidth(),
                         image.getHeight(),
                         0,
                         glFormat,
                         GL_UNSIGNED_BYTE,
                         image.getConstHandle());
            glGenerateMipmap(glTextureType);
            glBindTexture(glTextureType, 0);
        }
        case Type::TYPE_2D_ARRAY: { break; }
        case Type::TYPE_3D: { break; }
        case Type::TYPE_3D_ARRAY: { break; }
        default: { std::cout << "Unknown Texture::Type\n"; _break(); }
    }
}

void Texture::bind() const {
    glBindTexture(glTextureType, id);
}
