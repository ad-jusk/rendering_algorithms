#include "include/TgaBuffer.hpp"
#include "include/Rasterizer.hpp"
#include "include/Triangle.hpp"
#include "include/Matrix4.hpp"

#define M_1_180 (1. / 180.)

static float ToRad(float deg) { return static_cast<float>(deg * M_PI * M_1_180); }

int main() {

    TgaBuffer buffer(BUFFER_WIDTH, BUFFER_HEIGHT, BG_COLOR);
    Rasterizer rasterizer(&buffer);

    Triangle t(Vector3{-1.f, 0.3f, 1.f}, Vector3{0.f, -1.f, 1.f}, Vector3{1.f, 0.3f, 1.f});

    Matrix4 transform = Matrix4(1.f);

    transform *= Matrix4::Perspective(60, 1.f, 0.01f, 100.f);
    transform *= Matrix4::Scale(1, 1, 1);
    transform *= Matrix4::LookAt(Vector3{0.f, 0.f, 6.f}, Vector3{0.f, 0.f, 0.f}, Vector3{0.f, 1.f, 0.f});
    transform *= Matrix4::Translation(0, 1, 1);
    transform *= Matrix4::RotationX(ToRad(45));
    //transform *= Matrix4::RotationY(ToRad(45));
    transform *= Matrix4::RotationZ(ToRad(90));

    t.applyTransform(transform);
    
    rasterizer.drawTriangle(t);

    buffer.saveToFile(OUTPUT_PATH_TGA);

    return 0;
}
