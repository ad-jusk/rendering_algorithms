#include "../include/Rasterizer.hpp"

Rasterizer::Rasterizer(Buffer* buffer) {
    this->buffer = buffer;
}

void Rasterizer::drawTriangle(Point& A, Point& B, Point& C) {
    // TODO
    for(int i = A.getY(); i < B.getY(); i++) {
        for(int j = A.getX(); j < C.getX(); j++) {
            buffer->setPixel(j, i, 0xFF00FF);
        }
    }
}