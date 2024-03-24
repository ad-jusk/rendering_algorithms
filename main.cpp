#include <iostream>
#include <vector>
#include <cstdint>

#include "include/TgaBuffer.hpp"
#include "include/Rasterizer.hpp"

int main() {

    TgaBuffer buffer(BUFFER_WIDTH, BUFFER_HEIGHT, BG_COLOR);
    Rasterizer rasterizer(&buffer);


    Vector3 A(0.5f, -0.5f, 0.f);
    Vector3 B(0.5f, 0.5f, 0.f);
    Vector3 C(-0.5f, 0.5f, 0.f);

    rasterizer.drawTriangle(A, B, C);

    Vector3 D(-0.5f, -0.5f, 0.f);
    Vector3 E(0.5f, -0.5f, 0.f);
    Vector3 F(-0.5f, 0.5f, 0.f);

    rasterizer.drawTriangle(D, E, F);

    buffer.saveToFile(OUTPUT_PATH_TGA);

    return 0;
}
