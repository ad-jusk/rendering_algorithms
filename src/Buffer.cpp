#include "../include/Buffer.hpp"

Buffer::Buffer(int width, int height, uint32_t color) {
    this->width = width;
    this->height = height;
    this->color = color;
}

void Buffer::setColor(uint32_t color) {
    this->color = color;
}

void Buffer::setSize(int width, int height) {
    this->width = width;
    this->height = height;
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