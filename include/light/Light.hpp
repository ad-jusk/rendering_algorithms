#pragma once

#include "Vector3.hpp"

class Light {
    
    public:
        Vector3 lightColor;
        float diffuseStrength, specularStrength;

        Light() : lightColor(1.f), diffuseStrength(0.7f), specularStrength(0.5f) {}
};