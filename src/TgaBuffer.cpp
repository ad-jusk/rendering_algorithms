#include "TgaBuffer.hpp"

void TgaBuffer::saveToFile(const char* filename) {

        FILE* file = fopen(filename, "wb");

        if (!file) {
            std::cerr << "Error: Unable to open file " << filename << std::endl;
            return;
        }

        uint8_t header[18] = { 0,0,2,0,0,0,0,0,0,0,0,0,
            (uint8_t)(this->width%256), (uint8_t)(this->width/256),
            (uint8_t)(this->height%256), (uint8_t)(this->height/256),
            (uint8_t)(24), 0x20
        };

        fwrite(header, 18, 1, file);

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                uint32_t pixel = pixels.at(y * width + x);
                uint8_t red = (pixel >> 16) & 0xFF;
                uint8_t green = (pixel >> 8) & 0xFF;
                uint8_t blue = pixel & 0xFF;
                fputc(blue, file);
                fputc(green, file);
                fputc(red, file);
            }
        }

        fclose(file);
}