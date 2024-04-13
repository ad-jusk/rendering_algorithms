#pragma once

#include "light/Light.hpp"

class PointLight : public Light {

    public:
        Vector3 position;
        
        PointLight() : Light(), position((Vector3{0.f, 0.f, 0.f}).normalize()) {}
};