    #pragma once
    
    #include "Vector3.hpp"

    union Color {

        uint32_t hex;
        uint8_t bytes[3];

        Vector3 ToVector() const {
            return {
                bytes[0] / 255.f, // red
                bytes[1] / 255.f, // green
                bytes[2] / 255.f  // blue
            };
        }

        static Color FromVector(Vector3 vector) {
            Color color;
            Vector3 clamped = vector.clamp_0_1();
            color.bytes[0] = 255.f * clamped.x; // red
            color.bytes[1] = 255.f * clamped.y; // green
            color.bytes[2] = 255.f * clamped.z; // blue
            return color;
        }
    };