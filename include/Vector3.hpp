#pragma once

#include <iostream>
#include <vector>
#include <cstdint>
#include <cmath>
#include <algorithm>
#include <memory>
#include <array>

class Vector3 {

public:
    float x, y, z;

    Vector3() : x(0), y(0), z(0) {}
    explicit Vector3(float x) : x(x), y(x), z(x) {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 operator+(float scalar) const {
        return Vector3(scalar + x, scalar + y, scalar + z);
    }

    Vector3 operator-(float scalar) const {
        return Vector3(x - scalar, y - scalar, z - scalar);
    }

    Vector3 operator*(float scalar) const {
        return Vector3(scalar * x, scalar * y, scalar * z);
    }

    Vector3 operator/(float scalar) const {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }

    float operator*(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    friend Vector3 operator*(float scalar, const Vector3& vector) {
        return vector * scalar;
    }

    void operator+=(Vector3 const& another) { *this = *this + another; }
    
    void operator-=(Vector3 const& another) { *this = *this - another; }

    Vector3 cross(const Vector3& other) const {
        return Vector3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
    }

    static Vector3 cross(const Vector3& a, const Vector3& b) { return a.cross(b); }

    float dot(const Vector3& v) const { return x * v.x + y * v.y + z * v.z; }

    static float dot(const Vector3& a, const Vector3& b) { return a.dot(b); }

    Vector3 mul(const Vector3& v) const {
        Vector3 result;
        result.x = this->x * v.x;
        result.y = this->y * v.y;
        result.z = this->z * v.z;
        return result;
    }

    Vector3 normalize() const {
        return *this / length();
    }

    float length() const {
        return sqrt(x * x + y * y + z * z);
    }

    float distance(const Vector3& other) const {
        return (*this - other).length();
    }

    float angle(const Vector3& rhs) const {
        float dot = x * rhs.x + y * rhs.y + z * rhs.z;
        return acos(dot / (this->length() * rhs.length()));
    }

    Vector3 clamp_0_1() const {
        float x = this->x;
        float y = this->y;
        float z = this->z;

        if (x < 0) x = 0;
        if (y < 0) y = 0;
        if (z < 0) z = 0;

        if (x > 1) x = 1;
        if (y > 1) y = 1;
        if (z > 1) z = 1;

        return Vector3(x, y, z);
    }

    Vector3 clamp_0_255() const {
        Vector3 c =  clamp_0_1();

        c.x *= 255.f;
        c.y *= 255.f;
        c.z *= 255.f;
        
        c.x = std::min(c.x, 255.f);
        c.y = std::min(c.y, 255.f);
        c.z = std::min(c.z, 255.f);
        
        return c;
    }

    bool operator==(const Vector3& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator!=(const Vector3& other) const {
        return !(*this == other);
    }

    Vector3 operator-() const {
        return Vector3(-x, -y, -z);
    }

    Vector3 operator+() const {
        return Vector3(x, y, z);
    }

    Vector3& operator=(Vector3 const& another) {
        if (this == &another) {
            return *this;
        }

        this->x = another.x;
        this->y = another.y;
        this->z = another.z;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector3& vec) {
        os << "[" << vec.x << ", " << vec.y << ", " << vec.z << "]";
        return os;
    }

    friend class Vector4;
};