//
// Created by diego on 19/09/23.
//

#ifndef OPENGL_IMAGE_H
#define OPENGL_IMAGE_H

#include <string>
#include <cstdint>

class Image {
public:
    Image(const std::string& imagePath);
    ~Image();

    [[nodiscard]] const uint8_t* getConstHandle() const { return data; }
    [[nodiscard]] uint8_t* getHandle() { return data; }
    [[nodiscard]] int32_t getWidth() const { return m_Width; }
    [[nodiscard]] int32_t getHeight() const { return m_Height; }
    [[nodiscard]] int32_t getNrChannels() const { return m_NrChannels; }

private:
    int32_t m_Width = 0;
    int32_t m_Height = 0;
    int32_t m_NrChannels = 0;
    uint8_t* data = nullptr;
};


#endif //OPENGL_IMAGE_H
