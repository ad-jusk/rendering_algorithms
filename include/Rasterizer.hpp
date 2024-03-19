#pragma once

#include "Buffer.hpp"
#include "Point.hpp"

class Rasterizer {

    private:
        Buffer* buffer;
        float calculateEdgeFunction(Point& A, Point& B, Point& C);
    
    public:
        explicit Rasterizer(Buffer* buffer);
        void drawTriangle(Point& A, Point& B, Point& C);
        void changeCanonicToViewport(Point& p);
};