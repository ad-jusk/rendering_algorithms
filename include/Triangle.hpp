#pragma once

#include "Matrix4.hpp"

struct Triangle {

    Vector3 A, B, C;
    Vector3 norA, norB, norC;
    Vector3 colorA, colorB, colorC;

    Triangle() : Triangle(Vector3{0}, Vector3{0}, Vector3{0}) {}
    Triangle(const Vector3& A, const Vector3& B, const Vector3& C)
            : Triangle(A, B, C, Vector3{0.f}, Vector3{0.f}, Vector3{0.f}) {}
    Triangle(const Vector3& A, const Vector3& B, const Vector3& C,
            const Vector3& norA, const Vector3& norB, const Vector3& norC)
            : A(A), B(B), C(C),
              norA(norA), norB(norB), norC(norC),
              colorA(Vector3{0.f}), colorB(Vector3{0.f}), colorC(Vector3{0.f}){}

    void applyTransform(const Matrix4& transform) {

        const Vector4 transA = transform * Vector4(A, 1.f);
        A = Vector3(transA.x, transA.y, transA.z) / transA.w;

        const Vector4 transB = transform * Vector4(B, 1.f);
        B = Vector3(transB.x, transB.y, transB.z) / transB.w;

        const Vector4 transC = transform * Vector4(C, 1.f);
        C = Vector3(transC.x, transC.y, transC.z) / transC.w;
    }

    void applyTransformToNormal (const Matrix4& invModel) {
        Vector4 tA = invModel * Vector4(norA, 1.f);
        Vector4 tB = invModel * Vector4(norB, 1.f);
        Vector4 tC = invModel * Vector4(norC, 1.f);
        norA = Vector3(tA.x, tA.y, tA.z).normalize();
        norB = Vector3(tB.x, tB.y, tB.z).normalize();
        norC = Vector3(tC.x, tC.y, tC.z).normalize();
    }

    friend std::ostream& operator<<(std::ostream& os, const Triangle& t) {
        os << "A = " << t.A << " B = " << t.B << " C = " << t.C;
        return os;
    }
};