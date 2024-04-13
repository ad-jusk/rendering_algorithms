#pragma once

#include "Triangle.hpp"
#include "Matrix4.hpp"

class Shader {

    protected:
        Matrix4 model, view, projection, modelToProjection;
        Vector3 viewPos;

    public:
        virtual void preProcess() = 0;
        virtual void vertexShader(Triangle& triangle) const = 0;
};