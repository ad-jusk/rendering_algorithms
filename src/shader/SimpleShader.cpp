#include "shader/SimpleShader.hpp"

void SimpleShader::preProcess() {
    Matrix4 modelTemp = model;
    modelTemp[3] = Vector4{0.f, 0.f, 0.f, 1.f};
    invModel = modelTemp.Inverse().Transpose();
    modelToProjection = projection * view * model;
    viewPos = Vector3{view[3].x, view[3].y, view[3].z};
}

void SimpleShader::vertexShader(Triangle& triangle) const {
    triangle.applyTransform(modelToProjection);
    triangle.applyTransformToNormal(invModel);
}

void SimpleShader::pixelShader(
    const Vector3& interpolatedPosition,
    const Vector3& interpolatedNormal,
    const Vector3& interpolatedColor,
    Vector3& outColor) const {

        const Vector3 ambientColor = ambientLight.color * ambientLight.strength;

        Vector3 lightColor;

        auto calculateLight = [&] (const Light* light, const Vector3 lightDir) {
            const Vector3 diffuse = Sat(interpolatedNormal.dot(lightDir)) * light->diffuseStrength * light->lightColor;
            const Vector3 reflect = Reflect(-lightDir, interpolatedNormal);
            const Vector3 viewDir = (viewPos - interpolatedPosition).normalize();
            const float specularStrength = std::pow(std::max(Vector3::dot(viewDir, reflect), 0.f), 12);
            const Vector3 specular = specularStrength * light->specularStrength * light->lightColor;
            lightColor += (diffuse + specular);
        };

        const Vector3 lightDir = -directionalLight.direction;
        calculateLight(&directionalLight, lightDir);

        for (const PointLight& pointLight : pointLights) {
            const Vector3 lightDir = (pointLight.position - interpolatedPosition).normalize();
            calculateLight(&pointLight, lightDir);
        }

        outColor = (ambientColor + lightColor).clamp_0_1();
}