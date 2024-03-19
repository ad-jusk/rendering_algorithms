#include <iostream>
#include <vector>
#include <cstdint>

#include "include/TgaBuffer.hpp"
#include "include/Rasterizer.hpp"

int main() {

    TgaBuffer buffer(BUFFER_WIDTH, BUFFER_HEIGHT, COLOR);
    Rasterizer rasterizer(&buffer);

    Point A(-1.f, -1.f, 0.f);
    Point B(1.f, -1.f, 0.f);
    Point C(0.f, 0.f, 0.f);

    Point D(0.f, 0.f, 0.f);
    Point E(0.3f, 0.3f, 0.0f);
    Point F(-0.3f, 0.3f, 0.f);

    // Point D(-1.f, -1.f, 0.0f);
    // Point E(0.0f, 0.0f, 0.0f);
    // Point F(-1.f, 1.f, 0.f);

    rasterizer.drawTriangle(A, B, C);
    rasterizer.drawTriangle(D, E, F);

    buffer.saveToFile(OUTPUT_PATH_TGA);

    return 0;
}
