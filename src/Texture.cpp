#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

Texture::Texture(const std::string& path) : width(0), height(0) {

    int32_t channels;

    unsigned char* texture = stbi_load(path.c_str(), &width, &height, &channels, 3);

    if(texture == nullptr) {
        std::cout << "Failed to load texture from file " + path << std::endl;
        return;
    }

    pixels.resize(width * height);
    
    for (int32_t x = 0; x < width; ++x) {
        for (int32_t y = 0; y < height; ++y) {

            const int32_t byteNumber = 3 * (x + width * y);
            
            Color color{};
            color.bytes[0] = texture[byteNumber + 0];
            color.bytes[1] = texture[byteNumber + 1];
            color.bytes[2] = texture[byteNumber + 2];
            color.bytes[3] = 255.f;
            
            setPix(x, y, color.hex);
        }
    }

    delete[] texture;
}


Color Texture::sample(const Vector3& uv) const {

    float u = std::clamp(uv.x, 0.f, 1.f);
    float v = std::clamp(uv.y, 0.f, 1.f);
    
    const uint32_t x = std::round(u * (width - 1));
    const uint32_t y = std::round((height - 1) - v * (height - 1));
    const uint32_t hex = getPix(x, y);
    
    return {hex};
}