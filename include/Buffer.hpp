#pragma once

#include <iostream>
#include <vector>
#include <limits>
#include <cstdint>

#define BUFFER_WIDTH 500
#define BUFFER_HEIGHT 500
#define BG_COLOR 0xFFFFFFFF
#define OUTPUT_PATH_TGA "../res/output.tga"
#define OUTPUT_PATH_PNG "../res/output.png"

class Buffer {

    protected:
        int width, height;
        std::vector<uint32_t> pixels;
        std::vector<float> depthBuffer;

    public:
        Buffer();
        explicit Buffer(int width, int height, uint32_t color);
        void fillColor(uint32_t color);
        void fillDepth(float depth);
        void setSize(int width, int height, uint32_t color);
        int getWidth() const;
        int getHeight() const;
        virtual void saveToFile() const = 0;

        #define CALC_INDEX (x + width * y)

            uint32_t getPixel(uint32_t x, uint32_t y) const { return pixels[CALC_INDEX]; }
            void setPixel(uint32_t x, uint32_t y, uint32_t color) { pixels[CALC_INDEX] = color; }
            
            float getDepth(uint32_t x, uint32_t y) const { return depthBuffer[CALC_INDEX]; }
            void setDepth(uint32_t x, uint32_t y, float value) { depthBuffer[CALC_INDEX] = value; }

        #undef CALC_INDEX
};