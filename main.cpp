#include <iostream>
#include <vector>
#include <cstdint>

#include "include/TgaBuffer.hpp"
#include "include/Rasterizer.hpp"

int main() {

    TgaBuffer buffer(BUFFER_WIDTH, BUFFER_HEIGHT, COLOR);
    Rasterizer rasterizer(&buffer);

    Point A(10, 20);
    Point B(90, 100);
    Point C(300, 15);

    rasterizer.drawTriangle(A, B, C);

    buffer.saveToFile(OUTPUT_PATH_TGA);

    return 0;
}
