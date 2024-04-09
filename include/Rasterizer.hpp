#pragma once

#include "Buffer.hpp"
#include "Color.hpp"
#include "Triangle.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"

class Rasterizer {

    private:
        Buffer* buffer;
        void interpolizeTriangleColor(const Vector3& p, Vector3& A, Vector3& B, Vector3& C);
    
    public:
        explicit Rasterizer(Buffer* buffer);
        void render(Mesh* mesh, const Shader* shader);
        void drawTriangle(const Triangle& t);
        void changeCanonicToViewport(Vector3& p);
};