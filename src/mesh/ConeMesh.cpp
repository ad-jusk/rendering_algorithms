#include "mesh/ConeMesh.hpp"

ConeMesh::ConeMesh(float radius, float height, uint32_t segmentsNum) {
    
    // cone tip
    vertices.push_back(Vector3(0.f, height / 2.f, 0.f));

    // cap
    for (size_t i = 0; i < segmentsNum; i++) {
        float ratio = static_cast<float>(i) / (segmentsNum);
        float r = ratio * (M_PI * 2.0);
        float x = std::cos(r) * radius;
        float y = std::sin(r) * radius;
        vertices.push_back(Vector3(x, -height / 2.f, y));
    }

    // center of cone base
    vertices.push_back(Vector3(0.f, -height / 2.f, 0.f));

    // cap
    for (size_t i = 0; i < segmentsNum; i++) {
        uint32_t ii = (i + 1) % segmentsNum;
        vert_indicies.push_back(0);
        vert_indicies.push_back(i + 1);
        vert_indicies.push_back(ii + 1);
    }

    // reverse order
    std::reverse(vert_indicies.begin(), vert_indicies.end());

    // base
    for (size_t i = 0; i < segmentsNum; i++) {
        uint32_t ii = (i + 1) % segmentsNum;
        vert_indicies.push_back(vertices.size() - 1);
        vert_indicies.push_back(i + 1);
        vert_indicies.push_back(ii + 1);
    }

    norm_indicies.insert(norm_indicies.end(), vert_indicies.begin(), vert_indicies.end());
    normals.resize(segmentsNum + 2, Vector3{0.f});
    
    for (Vector3& normal : normals) {
        normal = Vector3{0.f};
    }

    for (int i = 0; i < vert_indicies.size(); i += 3) {
        Vector3 normal = Vector3::cross(
            (vertices[vert_indicies[i]] - vertices[vert_indicies[i + 1]]),
            (vertices[vert_indicies[i]] - vertices[vert_indicies[i + 2]])).normalize();

        normals[vert_indicies[i]] += normal;
        normals[vert_indicies[i + 1]] += normal;
        normals[vert_indicies[i + 2]] += normal;
    }

    for (Vector3& normal : normals) {
        normal = normal.normalize();
    }
}