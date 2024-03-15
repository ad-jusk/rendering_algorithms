#include <iostream>
#include <vector>
#include <cstdint>

#include "include/TgaBuffer.hpp"

int main() {
    TgaBuffer buffer(BUFFER_WIDTH, BUFFER_HEIGHT, COLOR);
    buffer.saveToFile(OUTPUT_PATH_TGA);
    return 0;
}
