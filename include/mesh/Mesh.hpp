#pragma once

#include "Triangle.hpp"

class Mesh {

    protected:
        std::vector<Vector3> vertices{};
        std::vector<uint32_t> vert_indicies{};
        Mesh();
    
    public:
        void GetTriangle(uint32_t index, Triangle& triangle) const;
        uint32_t GetNumTriangles() const {return vert_indicies.size() / 3.;}
};