#include "../include/Rasterizer.hpp"

Rasterizer::Rasterizer(Buffer* buffer) {
    this->buffer = buffer;
}

void Rasterizer::drawTriangle(Vector3& A, Vector3& B, Vector3& C) {

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

    const bool tl1 = ((A.y - B.y) < 0 || ((A.y - B.y) == 0 && (A.x - B.x) > 0));
    const bool tl2 = ((B.y - C.y) < 0 || ((B.y - C.y) == 0 && (B.x - C.x) > 0));
    const bool tl3 = ((C.y - A.y) < 0 || ((C.y - A.y) == 0 && (C.x - A.x) > 0));

    Vector3 p;

    for(int y = minY; y < maxY; y++) {
        for(int x = minX; x < maxX; x++) {

            p.x = x;
            p.y = y;
            
            const float ABP = calculateEdgeFunction(A, B, p);
            const float BCP = calculateEdgeFunction(B, C, p);
            const float CAP = calculateEdgeFunction(C, A, p);

            if((ABP > 0 || (ABP == 0 && tl1))
                && (BCP > 0 || (BCP == 0 && tl2))
                && (CAP > 0 || (CAP == 0 && tl3))) {
                interpolizeTriangleColor(p, A, B, C);
            }
        }
    }
}

float Rasterizer::calculateEdgeFunction(Vector3& A, Vector3& B, Vector3& C) {
    return (B.x - A.x) * (C.y - A.y) -
        (B.y - A.y) * (C.x - A.x);
}

void Rasterizer::changeCanonicToViewport(Vector3& p) {
    int x = (p.x + 1.f) * buffer->getWidth() * .5f;
    int y = (p.y + 1.f) * buffer->getHeight() * .5f;
    p.x = x;
    p.y = y;
}

void Rasterizer::interpolizeTriangleColor(const Vector3& p, Vector3& A, Vector3& B, Vector3& C) {

    const int32_t dx12 = A.x - B.x;
    const int32_t dx13 = A.x - C.x;
    const int32_t dx23 = B.x - C.x;
    const int32_t dx31 = C.x - A.x;
    const int32_t dx32 = C.x - B.x;
    
    const int32_t dy12 = A.y - B.y;
    const int32_t dy13 = A.y - C.y;
    const int32_t dy23 = B.y - C.y;
    const int32_t dy31 = C.y - A.y;

    const bool tl1 = (dy12 < 0 || (dy12 == 0 && dx12 > 0));
    const bool tl2 = (dy23 < 0 || (dy23 == 0 && dx23 > 0));
    const bool tl3 = (dy31 < 0 || (dy31 == 0 && dx31 > 0));

    const float barUDenominator = 1.f / (dy23 * dx13 + dx32 * dy13);
    const float barVDenominator = 1.f / (dy31 * dx23 + dx13 * dy23);

    const int32_t dxs3 = p.x - C.x;
    const int32_t dys3 = p.y - C.y;

    const float barU = (dy23 * dxs3 + dx32 * dys3) * barUDenominator;
    const float barV = (dy31 * dxs3 + dx13 * dys3) * barVDenominator;
    const float barW = 1.f - barU - barV;

    const float screenDepth = buffer->getDepth(p.x, p.y);
    const float currentDepth = barU * A.z + barV * B.z + barW * C.z;

    if(currentDepth < screenDepth) {

        Vector3 color1 = Color{0x0000FF}.ToVector();
        Vector3 color2 = Color{0xFF0000}.ToVector();
        Vector3 color3 = Color{0x00FF00}.ToVector();
        Vector3 finalColor = color1 * barU + color2  * barV + color3 * barW;
        uint32_t finalColorHex = Color::FromVector(finalColor).hex;

        buffer->setPixel(p.x, p.y, finalColorHex);
        buffer->setDepth(p.x, p.y, currentDepth);
    }
}