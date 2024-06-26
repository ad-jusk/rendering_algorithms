#include "mesh/Mesh.hpp"

Mesh::Mesh() {}

void Mesh::GetTriangle(uint32_t index, Triangle& triangle) const {
    
    uint32_t indiceID = index * 3;

    const uint32_t v1 = vert_indicies[indiceID];
    const uint32_t v2 = vert_indicies[indiceID + 1];
    const uint32_t v3 = vert_indicies[indiceID + 2];

    const uint32_t n1 = norm_indicies[indiceID];
    const uint32_t n2 = norm_indicies[indiceID + 1];
    const uint32_t n3 = norm_indicies[indiceID + 2];

    triangle.A = vertices[v1];
    triangle.B = vertices[v2];
    triangle.C = vertices[v3];

    triangle.norA = normals[n1];
    triangle.norB = normals[n2];
    triangle.norC = normals[n3];

    if (!uv_indicies.empty()) {
        const uint32_t uv1 = uv_indicies[indiceID];
        const uint32_t uv2 = uv_indicies[indiceID + 1];
        const uint32_t uv3 = uv_indicies[indiceID + 2];

        triangle.uvA = uvs[uv1];
        triangle.uvB = uvs[uv2];
        triangle.uvC = uvs[uv3];
    }
    else {
        triangle.uvA = Vector3{0.f};
        triangle.uvB = Vector3{0.f};
        triangle.uvC = Vector3{0.f};
    }
}