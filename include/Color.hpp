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
            Color result;
            Vector3 saturatedVec = vector.clamp_0_1();
            result.bytes[0] = 255.f * saturatedVec.x; // red
            result.bytes[1] = 255.f * saturatedVec.y; // green
            result.bytes[2] = 255.f * saturatedVec.z; // blue
            return result;
        }
    };