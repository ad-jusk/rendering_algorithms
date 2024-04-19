#pragma once

#include "Vector3.hpp"

struct AmbientLight {
    
    Vector3 color;
    float strength;

    AmbientLight() : color(Vector3{1.f}), strength(0.2) {}
    AmbientLight(const Vector3& color, float strength) : color(color), strength(strength) {}
};