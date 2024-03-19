#include <iostream>
#include <vector>
#include <cstdint>

#include "include/TgaBuffer.hpp"
#include "include/Rasterizer.hpp"

int main() {

    TgaBuffer buffer(BUFFER_WIDTH, BUFFER_HEIGHT, BG_COLOR);
    Rasterizer rasterizer(&buffer);

    Point A(-0.f, -0.8f, 0.f);
    Point B(0.7f, 0.4f, 0.f);
    Point C(-0.7f, 0.4f, 0.f);

    rasterizer.drawTriangle(A, B, C);

    buffer.saveToFile(OUTPUT_PATH_TGA);

    return 0;
}
