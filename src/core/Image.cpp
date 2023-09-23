//
// Created by diego on 19/09/23.
//

#include "Image.h"

#include "includes.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Image::Image(const std::string &imagePath) {
    data = stbi_load(imagePath.c_str(), &m_Width, &m_Height, &m_NrChannels, 0);

    if (data == nullptr) {
        std::cerr << "Failed to load image in: " << imagePath << "\n";
    } else {
        std::cout << "Created image successfully!\n";
    }
}

Image::~Image() {
    if (data != nullptr) {
        stbi_image_free(data);
    }
}
