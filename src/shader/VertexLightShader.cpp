#include "shader/VertexLightShader.hpp"

void VertexLightShader::preProcess() {
    Matrix4 modelTemp = model;
    modelTemp[3] = Vector4{0.f, 0.f, 0.f, 1.f};
    invModel = modelTemp.Inverse().Transpose();
    modelToProjection = projection * view * model;
    viewPos = Vector3{view[3].x, view[3].y, view[3].z};
}

void VertexLightShader::vertexShader(Triangle& triangle) const {

    triangle.applyTransform(modelToProjection);
    triangle.applyTransformToNormal(invModel);

    auto calculateColor = [&](Vector3& pos, Vector3& nor, Vector3& color) {

        const Vector3 ambientColor = ambientLight.color * ambientLight.strength;

        Vector3 lightColor;

        auto calculateLight = [&] (const Light* light, const Vector3 lightDir) {
            const Vector3 diffuse = Sat(nor.dot(lightDir)) * light->diffuseStrength * light->lightColor;
            const Vector3 reflect = Reflect(-lightDir, nor);
            const Vector3 viewDir = (viewPos - pos).normalize();
            const float specularStrength = std::pow(std::max(Vector3::dot(viewDir, reflect), 0.f), 12);
            const Vector3 specular = specularStrength * light->specularStrength * light->lightColor;
            lightColor += (diffuse + specular);
        };

        const Vector3 lightDir = -directionalLight.direction;
        calculateLight(&directionalLight, lightDir);

        for (const PointLight& pointLight : pointLights) {
            const Vector3 lightDir = (pointLight.position - pos).normalize();
            calculateLight(&pointLight, lightDir);
        }

        color = ambientColor + lightColor;
    };

    calculateColor(triangle.A, triangle.norA, triangle.colorA);
    calculateColor(triangle.B, triangle.norB, triangle.colorB);
    calculateColor(triangle.C, triangle.norC, triangle.colorC);
}

void VertexLightShader::pixelShader(
    const Vector3& interpolatedPosition,
    const Vector3& interpolatedNormal,
    const Vector3& interpolatedColor,
    const Vector3& interpolatedUV,
    Vector3& outColor) const {
    
    // SHADING DONE IN VERTEXES, RETURNING INTERPOLATED COLOR

    outColor = interpolatedColor;

}
