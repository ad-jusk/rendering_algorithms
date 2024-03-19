#pragma once

#include <iostream>

class Point {
    
    public:
        float x, y, z;
        Point(float x, float y) : x(x), y(y), z(0) {}
        Point(float x, float y, float z) : x(x), y(y), z(z) {}
        void setX(float x) { this->x = x; }
        void setY(float y) { this->y = y; }
        void setZ(float z) { this->z = z; }
};

inline std::ostream& operator<<(std::ostream& os, const Point& p) {
    return os << "p = ["  << p.x << ", " << p.y << ", " << p.z << "]" << std::endl;
}