#pragma once

#include "Buffer.hpp"

class PngBuffer : public Buffer {

    public:
        using Buffer::Buffer;
        void saveToFile() const override;
};

