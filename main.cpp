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
    directionalLight.diffuseStrength = 0.7f;
    directionalLight.specularStrength = 0.f;
    simpleShader->setDirectionalLight(directionalLight);

    // POINT LIGHT
    PointLight pointLight;
    pointLight.position = Vector3{0.f, -1.5f, 0.f};
    pointLight.lightColor = Vector3{1.f, 1.f, 1.f};
    pointLight.diffuseStrength = 0.7f;
    pointLight.specularStrength = 0.0f;
    simpleShader->addPointLight(pointLight);
    
    // TEXTURE
    std::shared_ptr<Texture> brickTexture = std::make_shared<Texture>("../res/textures/brick.png");
    std::shared_ptr<Texture> grassTexture = std::make_shared<Texture>("../res/textures/grass.jpg");
    simpleShader->setTexture(brickTexture);
    simpleShaderNoLight->setTexture(brickTexture);

    simpleShader->setProjection(Matrix4::Perspective(ToRad(60.f), 1.f, 0.01f, 100.f));
    simpleShader->setView(Matrix4::LookAt(Vector3{0.f, 0.f, 6.f}, Vector3{0.f, 0.f, 0.f}, Vector3{0.f, 1.f, 0.f}));

    simpleShaderNoLight->setProjection(Matrix4::Perspective(ToRad(60.f), 1.f, 0.01f, 100.f));
    simpleShaderNoLight->setView(Matrix4::LookAt(Vector3{0.f, 0.f, 6.f}, Vector3{0.f, 0.f, 0.f}, Vector3{0.f, 1.f, 0.f}));

    Matrix4 model = Matrix4{1};

    SphereMesh sphereMesh(32);
    model = Matrix4::Translation(-1.5f, -1.f, 0.f) *
            Matrix4::Scale(1.f, 1.f, 1.f);
    simpleShader->setModel(model);
    rasterizer.render(&sphereMesh, simpleShader.get());
    
    SphereMesh sphereMesh2(32);
    model = Matrix4::Translation(1.5f, -1.f, 0.f) *
            Matrix4::Scale(1.f, 1.f, 1.f);
    simpleShaderNoLight->setModel(model);
    rasterizer.render(&sphereMesh2, simpleShaderNoLight.get());
    
    SphereMesh sphereMesh3(32);

    model = Matrix4::Translation(0.f, 1.5f, 0.f) *
            Matrix4::Scale(1.f, 1.f, 1.f);
    simpleShader->setModel(model);
    simpleShader->setTexture(grassTexture);
    rasterizer.render(&sphereMesh3, simpleShader.get());

    rasterizer.saveToFile();

    return 0;
}
