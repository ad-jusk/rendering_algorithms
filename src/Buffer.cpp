#include "../include/Buffer.hpp"

Buffer::Buffer() {
    this->width = 0;
    this->height = 0;
    this->color = 0x000000;
}

Buffer::Buffer(int width, int height, uint32_t color) {
    this->width = width;
    this->height = height;
    this->color = color;
    this->pixels.resize(width * height, color);
}

void Buffer::setColor(uint32_t color) {
    this->color = color;
    std::fill(pixels.begin(), pixels.end(), color);
}

void Buffer::setSize(int width, int height) {
    this->width = width;
    this->height = height;
    this->pixels.resize(width * height, color);
}

void Buffer::setPixel(int x, int y, uint32_t color) {
    if (x >= 0 && x < this->width && y >= 0 && y < this->height) {
        this->pixels[y * width + x] = color;
    } else {
        std::cerr << "Pixel coordinates out of bounds!" << std::endl;
    }
}

uint32_t Buffer::getColor() {
    return this->color;
}

int Buffer::getHeight() {
    return this->height;
}

int Buffer::getWidth() {
    return this->width;
}