#pragma once

#include <iostream>
#include <cstdint>

#define BUFFER_WIDTH 500
#define BUFFER_HEIGHT 500
#define COLOR 0xFF0000
#define OUTPUT_PATH_TGA "../res/output.tga"

class Buffer {

    protected:
        int width, height;
        uint32_t color;

    public:
        explicit Buffer(int width, int height, uint32_t color);
        void setColor(uint32_t color);
        void setSize(int width, int height);
        int getWidth();
        int getHeight();
        uint32_t getColor();
        virtual void saveToFile(const char* filename) = 0;
};