#include "PngBuffer.hpp"
#include "lodepng.h"

void PngBuffer::saveToFile() const {

    std::vector<uint8_t> matrix;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            uint32_t pixel = pixels.at(y * width + x);
            uint8_t red = (pixel >> 16) & 0xFF;
            uint8_t green = (pixel >> 8) & 0xFF;
            uint8_t blue = pixel & 0xFF;
            matrix.push_back(red);
            matrix.push_back(green);
            matrix.push_back(blue);
        }
    }

    unsigned int error = lodepng::encode(OUTPUT_PATH_PNG, matrix, this->width, this->height, LCT_RGB);
	
    if (error) {
		std::cerr << "Lodepng error " << error << ": " << lodepng_error_text(error) << std::endl;
	}
	else {
		std::cout << "PNG image rendered" << std::endl;
	}
}