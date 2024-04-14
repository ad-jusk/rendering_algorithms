#pragma once

#include "Triangle.hpp"
#include "Matrix4.hpp"
#include "light/AmbientLight.hpp"
#include "light/DirectionalLight.hpp"
#include "light/PointLight.hpp"
#include "Utils.hpp"

class Shader {

    protected:
        Matrix4 model, view, projection, modelToProjection, invModel;
        Vector3 viewPos;
        AmbientLight ambientLight;
        DirectionalLight directionalLight;
        std::vector<PointLight> pointLights;

    public:
        virtual void preProcess() = 0;
        virtual void vertexShader(Triangle& triangle) const = 0;
};