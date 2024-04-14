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
    directionalLight.direction = Vector3{0, 0, 1}.normalize();
    directionalLight.lightColor = Vector3{1.f, 0.f, 0.f};
    directionalLight.diffuseStrength = 0.5f;
    directionalLight.specularStrength = 0.0f;
    shader->setDirectionalLight(directionalLight);

    // POINT LIGHT
    PointLight pointLight;
    pointLight.position = Vector3{0.f, 3.f, 0.f};
    pointLight.lightColor = {0.f, 0.f, 1.f};
    pointLight.diffuseStrength = 0.5f;
    shader->addPointLight(pointLight);

    PointLight pointLight2;
    pointLight2.position = Vector3{-3.f, 0.f, 0.f};
    pointLight2.lightColor = {0.f, 1.f, 1.f};
    pointLight2.diffuseStrength = 0.5f;
    shader->addPointLight(pointLight2);

    shader->setProjection(Matrix4::Perspective(ToRad(120.f), 1.f, 0.01f, 100.f));
    shader->setView(Matrix4::LookAt({0.f, 0.f, 10.f}, Vector3{0.f}, Vector3{0.f, 1.f, 0.f}));

    Matrix4 model = Matrix4{1};

    SphereMesh sphereMesh(16);
    model = Matrix4::Translation(-0.2f, -0.2f, -20.f) *
            Matrix4::Scale(0.3f, 0.3f, 0.3f);
    shader->setModel(model);
    rasterizer.render(&sphereMesh, shader.get());

    ConeMesh coneMesh(1.f, 2.f, 6);
    model = Matrix4::Translation(0.2f, 0.1f, -20.f) *
            Matrix4::RotationZ(ToRad(180.f)) *
            Matrix4::RotationX(ToRad(30.f)) *
            Matrix4::Scale(0.3f, 0.3f, 0.3f);
    shader->setModel(model);
    rasterizer.render(&coneMesh, shader.get());

    rasterizer.saveToFile();

    return 0;
}
