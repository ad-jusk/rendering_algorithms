#pragma once

#include "Vector4.hpp"

class Matrix4 {
    
private:
    static constexpr uint8_t SIZE_X = 4;
    static constexpr uint8_t SIZE_Y = 4;
    std::array<Vector4, 4> grid{};

public:
    Matrix4() : Matrix4(0) {}

    explicit Matrix4(float x) {
        for (int i = 0; i < SIZE_X; ++i) {
            for (int j = 0; j < SIZE_Y; ++j) {
                if (i == j)
                    grid[i][j] = x;
                else
                    grid[i][j] = 0;
            }
        }
    }

    Matrix4(const Matrix4& m) {
        for (int i = 0; i < SIZE_X; ++i) {
            for (int j = 0; j < SIZE_Y; ++j) {
                grid[i][j] = m.grid[i][j];
            }
        }
    }

    float operator[](const std::pair<int, int>& coordinates) const {
        return grid[coordinates.first][coordinates.second];
    }
    
    float& operator[](const std::pair<int, int>& coordinates) {
        return grid[coordinates.first][coordinates.second];
    }
    
    Vector4& operator[](const uint32_t index) {
        return grid[index];
    }
    
    const Vector4& operator[](const uint32_t index) const {
        return grid[index];
    }

    Matrix4 operator-() const {
        Matrix4 result(0);
        for (int i = 0; i < SIZE_X; ++i) {
            for (int j = 0; j < SIZE_Y; ++j) {
                result.grid[i][j] = -this->grid[i][j];
            }
        }
        return result;
    }

    Matrix4 operator+(const Matrix4& other) const {
        Matrix4 result(0);
        for (int i = 0; i < SIZE_X; ++i) {
            for (int j = 0; j < SIZE_Y; ++j) {
                result.grid[i][j] = grid[i][j] + other.grid[i][j];
            }
        }

        return result;
    }

    Matrix4 operator-(const Matrix4& other) const {
        Matrix4 result(0);
        for (int i = 0; i < SIZE_X; ++i) {
            for (int j = 0; j < SIZE_Y; ++j) {
                result.grid[i][j] = grid[i][j] - other.grid[i][j];
            }
        }

        return result;
    }

    Matrix4& operator=(const Matrix4& other) {
        for (int i = 0; i < SIZE_X; ++i) {
            for (int j = 0; j < SIZE_Y; ++j) {
                grid[i][j] = other.grid[i][j];
            }
        }

        return *this;
    }

    bool operator==(const Matrix4& other) const {
        for (int i = 0; i < SIZE_X; ++i) {
            for (int j = 0; j < SIZE_Y; ++j) {
                if(grid[i][j] != other.grid[i][j])
                    return false;
            }
        }
        return true;
    }

    void operator+=(const Matrix4& other) {
        *this = *this + other;
    }

    void operator-=(const Matrix4& other) {
        *this = *this - other;
    }

    Matrix4 operator*(const float scalar) const {
        Matrix4 result(0);
        for (int i = 0; i < SIZE_X; ++i) {
            for (int j = 0; j < SIZE_Y; ++j) {
                result.grid[i][j] = scalar * grid[i][j];
            }
        }
        return result;
    }

    void operator*=(float scalar) {
        *this = *this * scalar;
    }

    Matrix4 operator*(const Matrix4& other) const {
        Matrix4 result(0);
        for (int i = 0; i < SIZE_X; ++i) {
            for (int j = 0; j < SIZE_Y; ++j) {
                for (int k = 0; k < SIZE_X; ++k) {
                    result.grid[i][j] += grid[k][j] * other.grid[i][k];
                }
            }
        }

        return result;
    }

    void operator*=(const Matrix4& other) {
        *this = *this * other;
    }

    Matrix4 Transpose() const {
        Matrix4 result(0);

        for (int i = 0; i < SIZE_X; i++) {
            for (int j = 0; j < SIZE_Y; j++) {
                result.grid[i][j] = grid[j][i];
            }
        }
        return result;
    }

    float Det() const {
        float result = 1;
        Matrix4 helper(*this);
        for (int i = 0; i < 4; i++) {
            for (int k = i + 1; k < 4; k++) {
                const float coefficient = helper.grid[k][i] / helper.grid[i][i];
                for (int j = i; j < 4; j++)
                    helper.grid[k][j] = helper.grid[k][j] - coefficient * helper.grid[i][j];
            }
        }
        for (int i = 0; i < 4; i++)
            result *= helper.grid[i][i];
        return result;
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix4 &Matrix4) {
        for (int i = 0; i < 4; ++i) {
            os << "[ ";
            for (int j = 0; j < 4; ++j) {
                os << Matrix4.grid[j][i] << " ";
            }
            os << "]" << "\n";
        }
        return os;
    }

    static Matrix4 Translation(float x, float y, float z) {
        Matrix4 result(1);
        result[3] = Vector4{x, y, z, 1};

        return result;
    }

    static Matrix4 Scale(float x, float y, float z) {
        Matrix4 result(1);

        result[{0, 0}] = x;
        result[{1, 1}] = y;
        result[{2, 2}] = z;
        return  result;
    }

    static Matrix4 RotationX(float radians) {
        Matrix4 result(1);

        result[{1, 1}] = std::cos(radians);
        result[{2, 1}] = -std::sin(radians);
        result[{1, 2}] = std::sin(radians);
        result[{2, 2}] = std::cos(radians);
        return  result;
    }

    static Matrix4 RotationY(float radians) {
        Matrix4 result(1);

        result[{0, 0}] = std::cos(radians);
        result[{0, 2}] = std::sin(radians);
        result[{2, 0}] = -std::sin(radians);
        result[{2, 2}] = std::cos(radians);
        return  result;
    }

    static Matrix4 RotationZ(float radians) {
        Matrix4 result(1);

        result[{0, 0}] = std::cos(radians);
        result[{0, 1}] = -std::sin(radians);
        result[{1, 0}] = std::sin(radians);
        result[{1, 1}] = std::cos(radians);
        return  result;
    }

    static Matrix4 LookAt(const Vector3& eye, const Vector3& center, const Vector3& up) {

        Matrix4 result {1};

        const Vector3 forward = (center - eye).normalize();
        const Vector3 right = forward.cross(up);
        const Vector3 trueUp = right.cross(forward);

        result[0] = Vector4{right.x, trueUp.x, forward.x, 0};
        result[1] = Vector4{right.y, trueUp.y, forward.y, 0};
        result[2] = Vector4{right.z, trueUp.z, forward.z, 0};
        result[3] = Vector4{0., 0., 0., 1.};

        return result * Translation(-eye.x, -eye.y, -eye.z);
    }

    static Matrix4 Perspective(float fov, float aspect, float near, float far) {
        
        fov = fov * M_PI * (1.f / 180.f);

        Matrix4 result {0};
        const float f = std::cos(fov / 2.) / std::sin(fov / 2.);
        
        result[0] = Vector4{ f / aspect, 0, 0, 0};
        result[1] = Vector4{0, f, 0, 0};
        result[2] = Vector4{0, 0, -(far + near) / (near - far), 1.};
        result[3] = Vector4{0, 0, static_cast<float>(2.) * far * near / (near - far), 0.};

        return result;
    }
    
    Vector4 operator*(const Vector4& vec4) const {
        Vector4 result;
        result.x = vec4.x * grid[0][0] + vec4.y * grid[1][0] + vec4.z * grid[2][0] + vec4.w * grid[3][0];
        result.y = vec4.x * grid[0][1] + vec4.y * grid[1][1] + vec4.z * grid[2][1] + vec4.w * grid[3][1];
        result.z = vec4.x * grid[0][2] + vec4.y * grid[1][2] + vec4.z * grid[2][2] + vec4.w * grid[3][2];
        result.w = vec4.x * grid[0][3] + vec4.y * grid[1][3] + vec4.z * grid[2][3] + vec4.w * grid[3][3];
        return result;
    }
};