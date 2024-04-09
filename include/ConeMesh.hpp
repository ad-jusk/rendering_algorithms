#pragma once

#include "Mesh.hpp"

class ConeMesh : public Mesh {

    public:
        ConeMesh(float radius, float height, uint32_t segmentsNum);
};