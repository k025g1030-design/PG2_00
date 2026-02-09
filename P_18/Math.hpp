#pragma once


const int kWindowWidth = 1280;
const int kWindowHeight = 720;
const int SPEED = 10;
const int COOL_DOWN = 30;
const float B_ALIVE = 0.03f;

struct Vector2 {
    float x;
    float y;
    Vector2 operator+(const Vector2& r) const { return { x + r.x, y + r.y }; }
    Vector2 operator-(const Vector2& r) const { return { x - r.x, y - r.y }; }
    Vector2 operator*(float s) const { return { x * s, y * s }; }
    Vector2& operator+=(const Vector2& r) { x += r.x; y += r.y; return *this; }
};

