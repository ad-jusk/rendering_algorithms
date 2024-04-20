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

    std::unique_ptr<SimpleShader> simpleShader = std::make_unique<SimpleShader>();
    std::unique_ptr<SimpleShader> simpleShaderNoLight = std::make_unique<SimpleShader>();

    // AMBIENT LIGHT
    simpleShader->setAmbientLight(AmbientLight{Vector3{1.f, 1.f, 1.f}, 0.2f});
    
    // DIRECTIONAL LIGHT
    DirectionalLight directionalLight;
    directionalLight.direction = Vector3{0, -1, 0};
    directionalLight.lightColor = Vector3{1.f, 1.f, 1.f};
    directionalLight.diffuseStrength = 0.9f;
    directionalLight.specularStrength = 0.f;
    simpleShader->setDirectionalLight(directionalLight);

    // POINT LIGHT
    PointLight pointLight;
    pointLight.position = Vector3{0.f, 0.f, 0.f};
    pointLight.lightColor = Vector3{1.f, 1.f, 1.f};
    pointLight.diffuseStrength = 0.9f;
    pointLight.specularStrength = 0.f;
    simpleShader->addPointLight(pointLight);
    
    // TEXTURE
    std::shared_ptr<Texture> brickTexture = std::make_shared<Texture>("../res/textures/brick.jpeg");
    std::shared_ptr<Texture> universeTexture = std::make_shared<Texture>("../res/textures/universe.jpg");
    simpleShader->setTexture(brickTexture);
    simpleShaderNoLight->setTexture(brickTexture);

    simpleShader->setProjection(Matrix4::Perspective(ToRad(60.f), 1.f, 0.01f, 100.f));
    simpleShader->setView(Matrix4::LookAt(Vector3{0.f, 0.f, 6.f}, Vector3{0.f, 0.f, 0.f}, Vector3{0.f, 1.f, 0.f}));

    simpleShaderNoLight->setProjection(Matrix4::Perspective(ToRad(60.f), 1.f, 0.01f, 100.f));
    simpleShaderNoLight->setView(Matrix4::LookAt(Vector3{0.f, 0.f, 6.f}, Vector3{0.f, 0.f, 0.f}, Vector3{0.f, 1.f, 0.f}));

    Matrix4 model = Matrix4{1};

    SphereMesh sphereMesh(16);
    model = Matrix4::Translation(-1.5f, -1.f, 0.f) *
            Matrix4::Scale(1.2f, 1.2f, 1.2f);
    simpleShader->setModel(model);
    rasterizer.render(&sphereMesh, simpleShader.get());
    
    SphereMesh sphereMesh2(16);
    model = Matrix4::Translation(1.5f, -1.f, 0.f) *
            Matrix4::Scale(1.2f, 1.2f, 1.2f);
    simpleShaderNoLight->setModel(model);
    rasterizer.render(&sphereMesh2, simpleShaderNoLight.get());
    
    ConeMesh coneMesh(1.f, 2.f, 6);
    model = Matrix4::Translation(0.f, 1.5f, 0.f) *
            Matrix4::RotationZ(ToRad(180.f)) *
            Matrix4::Scale(1.f, 1.f, 1.f);
    simpleShader->setModel(model);
    simpleShader->setTexture(universeTexture);
    rasterizer.render(&coneMesh, simpleShader.get());

    rasterizer.saveToFile();

    return 0;
}
