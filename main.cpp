#include "include/TgaBuffer.hpp"
#include "include/Rasterizer.hpp"
#include "include/Triangle.hpp"
#include "include/Matrix4.hpp"

int main() {

    TgaBuffer buffer(BUFFER_WIDTH, BUFFER_HEIGHT, BG_COLOR);
    Rasterizer rasterizer(&buffer);

    Triangle t(Vector3{-1.f, 0.3f, 0.f}, Vector3{0.f, -1.f, 0.f}, Vector3{1.f, 0.3f, 0.f});

    Matrix4 transform = Matrix4(1.f);
    transform *= Matrix4::Perspective(90, 1.f, 0.01f, 100.f);
    transform *= Matrix4::LookAt(Vector3{0.f, 0.f, 2.f}, Vector3{0, 0, 0}, Vector3(0, 1, 0));

    t.applyTransform(transform);

    rasterizer.drawTriangle(t);

    buffer.saveToFile(OUTPUT_PATH_TGA);

    return 0;
}
