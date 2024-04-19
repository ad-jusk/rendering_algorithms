#pragma once

#include "Buffer.hpp"
#include "Color.hpp"
#include "Triangle.hpp"
#include "shader/Shader.hpp"
#include "mesh/Mesh.hpp"

class Rasterizer {

    private:
        Buffer* buffer;
        void colorTriangle(const Vector3& p, const Triangle& t,  const Shader* shader);
    
    public:
        explicit Rasterizer(Buffer* buffer);
        ~Rasterizer();
        void render(Mesh* mesh, const Shader* shader);
        void drawTriangle(const Triangle& t, const Shader* shader);
        void changeCanonicToViewport(Vector3& p);
        void saveToFile() const;
};