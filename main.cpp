#include <iostream>
#include <vector>
#include <cstdint>

#include "include/TgaBuffer.hpp"
#include "include/Rasterizer.hpp"

int main() {

    TgaBuffer buffer(BUFFER_WIDTH, BUFFER_HEIGHT, COLOR);
    Rasterizer rasterizer(&buffer);

    Point A(10, 20);
    Point B(300, 15);
    Point C(90, 100);

    Point D(400, 10);
    Point E(300, 450);
    Point F(100, 400);

    rasterizer.drawTriangle(A, B, C);
    rasterizer.drawTriangle(D, E, F);

    buffer.saveToFile(OUTPUT_PATH_TGA);

    return 0;
}
