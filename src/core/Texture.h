//
// Created by diego on 19/09/23.
//

#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H

#include <string>
#include <cstdint>

#include "Image.h"

class Texture {
public:
    enum class Type {
        TYPE_1D,
        TYPE_1D_ARRAY,
        TYPE_2D,
        TYPE_2D_ARRAY,
        TYPE_3D,
        TYPE_3D_ARRAY
    };

    enum class Format {
        RGB,
        RGBA
    };

public:
    Texture(const Image& image, Texture::Type type, Texture::Format format, uint32_t textureNumber);
    ~Texture() = default;

    void bind() const;
    [[nodiscard]] uint32_t getGlTextureId() const { return id; }

private:
    uint32_t id = 0;
    int32_t glTextureType = 0;
};


#endif //OPENGL_TEXTURE_H
