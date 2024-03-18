#pragma once

#include <iostream>

class Point {

    private:
        float x, y, z;
    
    public:
        Point(float x, float y) : x(x), y(y), z(0) {}
        Point(float x, float y, float z) : x(x), y(y), z(z) {}
        float getX() const { return x; }
        float getY() const { return y; }
        float getZ() const { return z; }
        void setX(float x) { this->x = x; }
        void setY(float y) { this->y = y; }
        void setZ(float z) { this->z = z; }
};

inline std::ostream& operator<<(std::ostream& os, const Point& p) {
    return os << "p = ["  << p.getX() << ", " << p.getY() << ", " << p.getZ() << "]" << std::endl;
}