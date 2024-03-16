#pragma once

#include "Buffer.hpp"
#include "Point.hpp"

class Rasterizer {

    private:
        Buffer* buffer;
    
    public:
        explicit Rasterizer(Buffer* buffer);
        void drawTriangle(Point& A, Point& B, Point& C);
};