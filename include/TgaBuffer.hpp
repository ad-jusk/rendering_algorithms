#pragma once

#include "Buffer.hpp"

class TgaBuffer : public Buffer {

    public:
        using Buffer::Buffer;
        void saveToFile(const char* filename);
};

