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