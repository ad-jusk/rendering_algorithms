#pragma once

class Point {

    private:
        int x, y, z;
    
    public:
        Point(int x, int y) : x(x), y(y), z(0) {}
        Point(int x, int y, int z) : x(x), y(y), z(z) {}
        int getX() { return x; }
        int getY() { return y; }
        int getZ() { return z; }
        void setX(int x) { this->x = x; }
        void setY(int y) { this->y = y; }
};