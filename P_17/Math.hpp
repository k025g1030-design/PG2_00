#pragma once

struct Vector2 {
    float x;
    float y;

    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }
    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }
    Vector2 operator*(const float& other) const {
        return Vector2(x * other, y * other);
    }
};
