#pragma once

#include "Math.hpp"

class Enemy {
public:
    static bool isHit;

public:
    Enemy(const Vector2& position, const Vector2& velocity, float radius)
        : position_(position), velocity_(velocity), radius_(radius) {
    }
    Vector2 GetPosition() const {
        return position_;
    }
    float GetRadius() const {
        return radius_;
    }
    virtual void Update() = 0;
    virtual void Draw() = 0;

protected:
    Vector2 position_;
    Vector2 velocity_;
    float radius_;

};