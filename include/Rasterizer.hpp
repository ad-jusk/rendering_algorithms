#pragma once

#include "Buffer.hpp"
#include "Color.hpp"
#include "Triangle.hpp"
#include "shader/Shader.hpp"
#include "mesh/Mesh.hpp"

class Rasterizer {

    private:
        Buffer* buffer;
        void interpolizeTriangleColor(const Vector3& p, const Vector3& A, const Vector3& B, const Vector3& C);
    
    public:
        explicit Rasterizer(Buffer* buffer);
        ~Rasterizer();
        void render(Mesh* mesh, const Shader* shader);
        void drawTriangle(const Triangle& t);
        void changeCanonicToViewport(Vector3& p);
        void saveToFile() const;
};