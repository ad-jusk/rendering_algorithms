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

    Vector3 G(-0.5f, -0.7f, 1.f);
    Vector3 H(0.5f, -0.7f, 1.f);
    Vector3 I(0.f, 0.5f, -1.f);

    rasterizer.drawTriangle(G, H, I);

    buffer.saveToFile(OUTPUT_PATH_TGA);

    return 0;
}
