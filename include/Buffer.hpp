#pragma once

#include <iostream>
#include <vector>
#include <cstdint>

#define BUFFER_WIDTH 500
#define BUFFER_HEIGHT 500
#define BG_COLOR 0xFFFFFFFF
#define OUTPUT_PATH_TGA "../res/output.tga"

class Buffer {

    protected:
        int width, height;
        std::vector<uint32_t> pixels;

    public:
        Buffer();
        explicit Buffer(int width, int height, uint32_t color);
        void fillColor(uint32_t color);
        void setSize(int width, int height, uint32_t color);
        int getWidth() const;
        int getHeight() const;
        virtual void saveToFile(const char* filename) {};

        #define CALC_INDEX (x + width * y)

            uint32_t getPixel(uint32_t x, uint32_t y) const { return pixels[CALC_INDEX]; }
            void setPixel(uint32_t x, uint32_t y, uint32_t color) { pixels[CALC_INDEX] = color; }
            
            float getDepth(uint32_t x, uint32_t y) const { /*TODO*/ return 0; }
            void setDepth(uint32_t x, uint32_t y, float value) { /*TODO*/ }

        #undef CALC_INDEX
};