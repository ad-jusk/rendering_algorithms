#include "../include/Rasterizer.hpp"

Rasterizer::Rasterizer(Buffer* buffer) {
    this->buffer = buffer;
}

void Rasterizer::drawTriangle(Point& A, Point& B, Point& C) {

    changeCanonicToViewport(A);
    changeCanonicToViewport(B);
    changeCanonicToViewport(C);

    const float ABC = calculateEdgeFunction(A, B, C);
    
    if(ABC < 0) {
        return;
    }

    Point P(0, 0);

    const int minX = std::min(std::min(A.getX(), B.getX()), C.getX());
    const int minY = std::min(std::min(A.getY(), B.getY()), C.getY());
    const int maxX = std::max(std::max(A.getX(), B.getX()), C.getX());
    const int maxY = std::max(std::max(A.getY(), B.getY()), C.getY());

    for(int i = minY; i < maxY; i++) {
        for(int j = minX; j < maxX; j++) {

            if(i < 0 || i > buffer->getHeight()) continue;
            if(j < 0 || j > buffer->getWidth()) continue;

            P.setX(j);
            P.setY(i);
            
            const float ABP = calculateEdgeFunction(A, B, P);
            const float BCP = calculateEdgeFunction(B, C, P);
            const float CAP = calculateEdgeFunction(C, A, P);

            if(ABP > 0 && BCP > 0 && CAP > 0) {
                buffer->setPixel(P.getX(), P.getY(), 0x0000FF);
            }
        }
    }
}

float Rasterizer::calculateEdgeFunction(Point& A, Point& B, Point& C) {
    return (B.getX() - A.getX()) * (C.getY() - A.getY()) -
        (B.getY() - A.getY()) * (C.getX() - A.getX());
}

void Rasterizer::changeCanonicToViewport(Point& p) {
    int x = (p.getX() + 1.f) * buffer->getWidth() * .5f;
    int y = (p.getY() + 1.f) * buffer->getHeight() * .5f;
    p.setX(x);
    p.setY(y);
}