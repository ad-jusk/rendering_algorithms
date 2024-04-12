#include "Shader.hpp"

void Shader::preProcess() {
    Matrix4 modelTemp = model;
    modelTemp[3] = Vector4{0.f, 0.f, 0.f, 1.f};
    modelToProjection = projection * view * model;
    viewPos = Vector3{view[3].x, view[3].y, view[3].z};
}

void Shader::vertexShader(Triangle& triangle) const {
    triangle.applyTransform(modelToProjection);
}