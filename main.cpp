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

    std::unique_ptr<VertexLightShader> vertexShader = std::make_unique<VertexLightShader>();
    std::unique_ptr<SimpleShader> simpleShader = std::make_unique<SimpleShader>();

    // AMBIENT LIGHT
    vertexShader->setAmbientLight(AmbientLight{Vector3{1.f, 0.f, 0.f}, 0.1f});
    simpleShader->setAmbientLight(AmbientLight{Vector3{1.f, 0.f, 0.f}, 0.1f});
    
    // DIRECTIONAL LIGHT
    DirectionalLight directionalLight;
    directionalLight.direction = Vector3{0, -1, 0};
    directionalLight.lightColor = Vector3{1.f, 0.f, 0.f};
    directionalLight.diffuseStrength = 0.5f;
    directionalLight.specularStrength = 1.f;
    vertexShader->setDirectionalLight(directionalLight);
    simpleShader->setDirectionalLight(directionalLight);

    // POINT LIGHT
    PointLight pointLight;
    pointLight.position = Vector3{0.f, -1.5f, 0.f};
    pointLight.lightColor = Vector3{0.f, 0.f, 1.f};
    pointLight.diffuseStrength = 0.7f;
    pointLight.specularStrength = 0.0f;
    vertexShader->addPointLight(pointLight);
    simpleShader->addPointLight(pointLight);
    
    PointLight pointLight2;
    pointLight2.position = Vector3{0.f, 0.f, 0.5f};
    pointLight2.lightColor = Vector3{0.f, 1.f, 0.f};
    pointLight2.diffuseStrength = 0.5f;
    pointLight2.specularStrength = 0.0f;
    vertexShader->addPointLight(pointLight2);
    simpleShader->addPointLight(pointLight2);

    vertexShader->setProjection(Matrix4::Perspective(ToRad(60.f), 1.f, 0.01f, 100.f));
    vertexShader->setView(Matrix4::LookAt(Vector3{0.f, 0.f, 5.f}, Vector3{0.f, 0.f, 0.f}, Vector3{0.f, 1.f, 0.f}));
    
    simpleShader->setProjection(Matrix4::Perspective(ToRad(60.f), 1.f, 0.01f, 100.f));
    simpleShader->setView(Matrix4::LookAt(Vector3{0.f, 0.f, 5.f}, Vector3{0.f, 0.f, 0.f}, Vector3{0.f, 1.f, 0.f}));

    Matrix4 model = Matrix4{1};

    SphereMesh sphereMesh(16);
    model = Matrix4::Translation(-1.5f, -1.f, 0.f) *
            Matrix4::Scale(1.f, 1.f, 1.f);
    vertexShader->setModel(model);
    rasterizer.render(&sphereMesh, vertexShader.get());
    
    SphereMesh sphereMesh2(16);
    model = Matrix4::Translation(1.5f, -1.f, 0.f) *
            Matrix4::Scale(1.f, 1.f, 1.f);
    simpleShader->setModel(model);
    rasterizer.render(&sphereMesh2, simpleShader.get());

    ConeMesh coneMesh(1.f, 2.f, 20);
    model = Matrix4::Translation(0.f, 1.f, 0.f) *
            Matrix4::RotationZ(ToRad(180.f)) *
            Matrix4::Scale(0.9f, 0.9f, 0.9f);
    vertexShader->setModel(model);
    rasterizer.render(&coneMesh, vertexShader.get());

    rasterizer.saveToFile();

    return 0;
}
