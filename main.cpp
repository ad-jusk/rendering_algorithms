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

int main() {

    Rasterizer rasterizer(new PngBuffer(BUFFER_WIDTH, BUFFER_HEIGHT, BG_COLOR));

    std::unique_ptr<VertexLightShader> shader = std::make_unique<VertexLightShader>();

    // AMBIENT LIGHT
    shader->setAmbientLight(AmbientLight{Vector3{1.f, 0.f, 0.f}, 0.1f});
    
    // DIRECTIONAL LIGHT
    DirectionalLight directionalLight;
    directionalLight.direction = Vector3{0, -1, 0};
    directionalLight.lightColor = Vector3{1.f, 0.f, 0.f};
    directionalLight.diffuseStrength = 0.5f;
    directionalLight.specularStrength = 0.5f;
    shader->setDirectionalLight(directionalLight);

    // POINT LIGHT
    PointLight pointLight;
    pointLight.position = Vector3{0.f, -1.5f, 0.f};
    pointLight.lightColor = Vector3{0.f, 0.f, 1.f};
    pointLight.diffuseStrength = 0.7f;
    pointLight.specularStrength = 0.0f;
    shader->addPointLight(pointLight);

    shader->setProjection(Matrix4::Perspective(ToRad(60.f), 1.f, 0.01f, 100.f));
    shader->setView(Matrix4::LookAt(Vector3{0.f, 0.f, 5.f}, Vector3{0.f, 0.f, 0.f}, Vector3{0.f, 1.f, 0.f}));

    Matrix4 model = Matrix4{1};

    SphereMesh sphereMesh(16);
    model = Matrix4::Translation(-1.5f, -1.f, 0.f) *
            Matrix4::Scale(1.f, 1.f, 1.f);
    shader->setModel(model);
    rasterizer.render(&sphereMesh, shader.get());
    
    SphereMesh sphereMesh2(16);
    model = Matrix4::Translation(1.5f, -1.f, 0.f) *
            Matrix4::Scale(1.f, 1.f, 1.f);
    shader->setModel(model);
    rasterizer.render(&sphereMesh2, shader.get());

    ConeMesh coneMesh(1.f, 2.f, 6);
    model = Matrix4::Translation(0.f, 1.5f, 0.f) *
            Matrix4::RotationX(ToRad(45.f)) *
            Matrix4::Scale(0.9f, 0.9f, 0.9f);
    shader->setModel(model);
    rasterizer.render(&coneMesh, shader.get());

    rasterizer.saveToFile();

    return 0;
}
