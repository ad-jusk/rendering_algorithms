#pragma once

#include "Vector3.hpp"

class Vector4 {
    
public:
    float x, y, z, w;

    Vector4() : x(0), y(0), z(0), w(0) {};
    explicit Vector4(float x) : x(x), y(x), z(x), w(x) {};
    Vector4(const Vector3& vec3, float w) : x(vec3.x), y(vec3.y), z(vec3.z), w(w) {}
    Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    float length() const { return std::sqrt(x * x + y * y + z * z + w * w); }

    Vector4 normal() const {
        double length = this->length();
        if (length < std::numeric_limits<float>::min())
            return Vector4{0.};

        return *this / length;
    }

    float Dot(const Vector4& rhs) const { return x * rhs.x + y * rhs.y + z * rhs.z; }
    static float Dot(const Vector4& a, Vector4& b) { return a.Dot(b); }

    float Angle(Vector4& rhs) const { return acos(this->Dot(rhs) / (this->length() * rhs.length())); }

    Vector4& operator=(Vector4 const& another) {
        if (this == &another) {
            return *this;
        }
        this->x = another.x;
        this->y = another.y;
        this->z = another.z;
        this->w = another.w;
        return *this;
    }

    Vector4 operator-() const {
        Vector4 result;
        result.x = -this->x;
        result.y = -this->y;
        result.z = -this->z;
        result.w = -this->w;
        return result;
    }

    Vector4 operator+(Vector4 const& another) const {
        Vector4 result;
        result.x = this->x + another.x;
        result.y = this->y + another.y;
        result.z = this->z + another.z;
        result.w = this->w + another.w;
        return result;
    }

    float operator[] (const uint8_t index) const {
        const float values[] = {x, y, z, w};
        return values[index];
    }
    
    float& operator[] (const uint8_t index) {
        float* values[] = {&x, &y, &z, &w};
        return *values[index];
    }

    Vector4 operator-(Vector4 const& another) const {
        Vector4 result = *this + (-another);
        return result;
    }

    void operator+=(Vector4 const& another) { *this = *this + another; }
    void operator-=(Vector4 const& another) { *this = *this - another; }

    Vector4 operator*(float const& scalar) const {
        Vector4 result;
        result.x = this->x * scalar;
        result.y = this->y * scalar;
        result.z = this->z * scalar;
        result.w = this->w * scalar;
        return result;
    }

    Vector4 operator/(float const& scalar) const {
        Vector4 result;
        result.x = this->x / scalar;
        result.y = this->y / scalar;
        result.z = this->z / scalar;
        result.w = this->w / scalar;
        return result;
    }

    void operator*=(float const& scalar) { *this = *this * scalar; }
    void operator/=(float const& scalar) { *this = *this / scalar; }
    bool operator==(const Vector4& rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w; }
    bool operator!=(const Vector4& rhs) const { return !(rhs == *this); }

    friend std::ostream& operator<<(std::ostream& os, const Vector4& vector4) {
        os << "[" << vector4.x << "," << vector4.y << "," << vector4.z << "," << vector4.w << "]";
        return os;
    }
    
    friend class Matrix4;
    friend class Vector3;
};