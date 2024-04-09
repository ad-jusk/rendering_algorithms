#include "include/TgaBuffer.hpp"
#include "include/Rasterizer.hpp"
#include "include/Triangle.hpp"
#include "include/Matrix4.hpp"
#include "include/SphereMesh.hpp"
#include "include/ConeMesh.hpp"

#define M_1_180 (1. / 180.)

static float ToRad(float deg) { return static_cast<float>(deg * M_PI * M_1_180); }

int main() {

    TgaBuffer buffer(BUFFER_WIDTH, BUFFER_HEIGHT, BG_COLOR);
    Rasterizer rasterizer(&buffer);

    Shader* shader = new Shader();

    shader->SetProjection(Matrix4::Perspective(ToRad(120.f), 1.f, 0.01f, 100.f));
    shader->SetView(Matrix4::LookAt({0.f, 0.f, 10.f}, Vector3{0.f}, Vector3{0.f, 1.f, 0.f}));

    Matrix4 model = Matrix4{1};

    SphereMesh sphereMesh(16);
    model = Matrix4::Translation(-0.2f, -0.2f, -20.f) *
            Matrix4::Scale(0.3f, 0.3f, 0.3f);
    shader->SetModel(model);
    rasterizer.render(&sphereMesh, shader);

    ConeMesh coneMesh(1.f, 2.f, 6);
    model = Matrix4::Translation(0.2f, 0.1f, -20) *
            Matrix4::RotationZ(ToRad(180.f)) *
            Matrix4::RotationX(ToRad(-60.f)) *
            Matrix4::Scale(0.3f, 0.3f, 0.3f);
    shader->SetModel(model);
    rasterizer.render(&coneMesh, shader);

    buffer.saveToFile(OUTPUT_PATH_TGA);

    delete shader;

    return 0;
}
