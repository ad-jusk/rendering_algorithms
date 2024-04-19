#pragma once

#include "Vector3.hpp"

#define M_1_180 (1. / 180.)

static float ToRad(float deg) { return static_cast<float>(deg * M_PI * M_1_180); }

static float Sat(float x) { return std::min(1.f, std::max(0.f, x)); }

static Vector3 Reflect(const Vector3& dirIn, const Vector3& normal) {
    return dirIn - 2 * Vector3::dot(dirIn, normal) * normal;
}