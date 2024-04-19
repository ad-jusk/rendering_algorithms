#pragma once

#include "Vector3.hpp"

class Light {
    
    public:
        Vector3 lightColor;
        float diffuseStrength, specularStrength;

        Light() : lightColor(Vector3{1.f, 1.f, 1.f}), diffuseStrength(0.f), specularStrength(0.f) {}
};