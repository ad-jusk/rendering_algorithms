#pragma once

#include "Color.hpp"

class Texture {

    private:
        std::vector<uint32_t> pixels;
        int width, height;
    
    public:
        Texture(const std::string& path);
        Color sample(const Vector3& uv) const;
        uint32_t getPix(int x, int y) const { return pixels[x + width * y]; }
        void setPix(int x, int y, uint32_t color) { pixels[x + width * y] = color; }
};