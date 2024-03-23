#include "../include/Buffer.hpp"

Buffer::Buffer() {
    this->width = 0;
    this->height = 0;
}

Buffer::Buffer(int width, int height, uint32_t color) {
    this->width = width;
    this->height = height;
    this->pixels.resize(width * height, color);
}

void Buffer::fillColor(uint32_t color) {
    std::fill(pixels.begin(), pixels.end(), color);
}

void Buffer::setSize(int width, int height, uint32_t color) {
    this->width = width;
    this->height = height;
    this->pixels.resize(width * height, color);
}

int Buffer::getHeight() const {
    return this->height;
}

int Buffer::getWidth()const  {
    return this->width;
}