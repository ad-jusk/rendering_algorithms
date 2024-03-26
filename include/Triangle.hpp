#pragma once

#include "Matrix4.hpp"

struct Triangle {

    Vector3 A, B, C;

    Triangle() : Triangle(Vector3{0}, Vector3{0}, Vector3{0}) {}
    Triangle(const Vector3& A, const Vector3& B, const Vector3& C): A(A), B(B), C(C) {}

    void applyTransform(const Matrix4& transform) {

        const Vector4 transA = transform * Vector4(A, 1.f);
        A = Vector3(transA.x, transA.y, transA.z) / transA.w;

        const Vector4 transB = transform * Vector4(B, 1.f);
        B = Vector3(transB.x, transB.y, transB.z) / transB.w;

        const Vector4 transC = transform * Vector4(C, 1.f);
        C = Vector3(transC.x, transC.y, transC.z) / transC.w;
    }

    friend std::ostream& operator<<(std::ostream& os, const Triangle& t) {
        os << "A = " << t.A << " B = " << t.B << " C = " << t.C;
        return os;
    }
};