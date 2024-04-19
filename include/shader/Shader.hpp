#pragma once

#include "Triangle.hpp"
#include "Matrix4.hpp"
#include "light/AmbientLight.hpp"
#include "light/DirectionalLight.hpp"
#include "light/PointLight.hpp"
#include "Utils.hpp"
#include "Texture.hpp"

class Shader {

    protected:
        Matrix4 model, view, projection, modelToProjection, invModel;
        Vector3 viewPos;
        AmbientLight ambientLight;
        DirectionalLight directionalLight;
        std::vector<PointLight> pointLights;
        std::shared_ptr<Texture> texture;

    public:
        virtual void preProcess() = 0;
        virtual void vertexShader(Triangle& triangle) const = 0;
        virtual void pixelShader(
                const Vector3& interpolatedPosition,
                const Vector3& interpolatedNormal,
                const Vector3& interpolatedColor,
                const Vector3& interpolatedUV,
                Vector3& outColor) const = 0;
};