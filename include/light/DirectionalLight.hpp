#pragma once

#include "light/Light.hpp"

class DirectionalLight : public Light {
    
    public:
        Vector3 direction;

        DirectionalLight() : Light(), direction((Vector3{-1.f, -1.f, 1.f}).normalize()) {}
};