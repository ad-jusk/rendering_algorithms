#pragma once

#include "Triangle.hpp"
#include "Matrix4.hpp"

class Shader {

    private:
        Matrix4 model, view, projection, modelToProjection;
        Vector3 viewPos;

    public:
        void preProcess();
        void vertexShader(Triangle& triangle) const;
        void SetModel(const Matrix4& newModel) { model = newModel; preProcess(); }
        void SetView(const Matrix4& newView) { view = newView; preProcess(); }
        void SetProjection(const Matrix4& newProjection) { projection = newProjection; preProcess(); }
};