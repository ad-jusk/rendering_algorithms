#pragma once

#include "Buffer.hpp"
#include "Color.hpp"

class Rasterizer {

    private:
        Buffer* buffer;
        float calculateEdgeFunction(Vector3& A, Vector3& B, Vector3& C);
        void interpolizeTriangleColor(const Vector3& p, Vector3& A, Vector3& B, Vector3& C);
    
    public:
        explicit Rasterizer(Buffer* buffer);
        void drawTriangle(Vector3& A, Vector3& B, Vector3& C);
        void changeCanonicToViewport(Vector3& p);
};