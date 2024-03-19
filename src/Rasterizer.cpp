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

    int minX = std::min(std::min(A.x, B.x), C.x);
    int minY = std::min(std::min(A.y, B.y), C.y);
    int maxX = std::max(std::max(A.x, B.x), C.x);
    int maxY = std::max(std::max(A.y, B.y), C.y);

    minX = std::max(minX, 0);
    minY = std::max(minY, 0);
    maxX = std::min(maxX, buffer->getWidth());
    maxY = std::min(maxY, buffer->getHeight());

    Point P(0, 0);

    for(int y = minY; y < maxY; y++) {
        for(int x = minX; x < maxX; x++) {

            P.setX(x);
            P.setY(y);
            
            const float ABP = calculateEdgeFunction(A, B, P);
            const float BCP = calculateEdgeFunction(B, C, P);
            const float CAP = calculateEdgeFunction(C, A, P);

            if(ABP > 0 && BCP > 0 && CAP > 0) {
                buffer->setPixel(P.x, P.y, interpolizeTriangleColor(P, A, B, C));
            }
        }
    }
}

float Rasterizer::calculateEdgeFunction(Point& A, Point& B, Point& C) {
    return (B.x - A.x) * (C.y - A.y) -
        (B.y - A.y) * (C.x - A.x);
}

void Rasterizer::changeCanonicToViewport(Point& p) {
    int x = (p.x + 1.f) * buffer->getWidth() * .5f;
    int y = (p.y + 1.f) * buffer->getHeight() * .5f;
    p.setX(x);
    p.setY(y);
}

uint32_t Rasterizer::interpolizeTriangleColor(Point& p, Point& A, Point& B, Point& C) {

    const int32_t dx12 = A.x - B.x;
    const int32_t dx13 = A.x - C.x;
    const int32_t dx23 = B.x - C.x;
    const int32_t dx31 = C.x - A.x;
    const int32_t dx32 = C.x - B.x;
    
    const int32_t dy12 = A.y - B.y;
    const int32_t dy13 = A.y - C.y;
    const int32_t dy23 = B.y - C.y;
    const int32_t dy31 = C.y - A.y;

    const float barUDenominator = 1.f / (dy23 * dx13 + dx32 * dy13);
    const float barVDenominator = 1.f / (dy31 * dx23 + dx13 * dy23);

    const int32_t dxs3 = p.x - C.x;
    const int32_t dys3 = p.y - C.y;

    const float barU = (dy23 * dxs3 + dx32 * dys3) * barUDenominator;
    const float barV = (dy31 * dxs3 + dx13 * dys3) * barVDenominator;
    const float barW = 1.f - barU - barV;

    int32_t r = barU * 0xFF;
    int32_t g = barV * 0xFF;
    int32_t b = barW * 0xFF;

    uint32_t color = (r << 16) | (g << 8) | b;

    return color;
}