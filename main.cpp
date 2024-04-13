#include <memory>

#include "TgaBuffer.hpp"
#include "PngBuffer.hpp"
#include "Rasterizer.hpp"
#include "Triangle.hpp"
#include "Matrix4.hpp"
#include "mesh/SphereMesh.hpp"
#include "mesh/ConeMesh.hpp"
#include "shader/SimpleShader.hpp"
#include "shader/VertexLightShader.hpp"

#define M_1_180 (1. / 180.)

static float ToRad(float deg) { return static_cast<float>(deg * M_PI * M_1_180); }

int main() {

    Rasterizer rasterizer(new PngBuffer(BUFFER_WIDTH, BUFFER_HEIGHT, BG_COLOR));

    std::unique_ptr<SimpleShader> shader = std::make_unique<SimpleShader>();
    //std::unique_ptr<VertexLightShader> shader = std::make_unique<VertexLightShader>();

    shader->setProjection(Matrix4::Perspective(ToRad(120.f), 1.f, 0.01f, 100.f));
    shader->setView(Matrix4::LookAt({0.f, 0.f, 10.f}, Vector3{0.f}, Vector3{0.f, 1.f, 0.f}));

    Matrix4 model = Matrix4{1};

    SphereMesh sphereMesh(16);
    model = Matrix4::Translation(-0.2f, -0.2f, -20.f) *
            Matrix4::Scale(0.3f, 0.3f, 0.3f);
    shader->setModel(model);
    rasterizer.render(&sphereMesh, shader.get());

    ConeMesh coneMesh(1.f, 2.f, 6);
    model = Matrix4::Translation(0.2f, 0.1f, -20) *
            Matrix4::RotationZ(ToRad(180.f)) *
            Matrix4::RotationX(ToRad(30.f)) *
            Matrix4::Scale(0.3f, 0.3f, 0.3f);
    shader->setModel(model);
    rasterizer.render(&coneMesh, shader.get());

    rasterizer.saveToFile();

    return 0;
}
