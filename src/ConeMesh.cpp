#include "ConeMesh.hpp"

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
}