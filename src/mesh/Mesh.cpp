#include "mesh/Mesh.hpp"

Mesh::Mesh() {}

void Mesh::GetTriangle(uint32_t index, Triangle& triangle) const {
    uint32_t indiceID = index * 3;

    const uint32_t v1 = vert_indicies[indiceID];
    const uint32_t v2 = vert_indicies[indiceID + 1];
    const uint32_t v3 = vert_indicies[indiceID + 2];

    triangle.A = vertices[v1];
    triangle.B = vertices[v2];
    triangle.C = vertices[v3];
}