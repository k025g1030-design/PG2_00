#pragma once

#include "Enemy.hpp"
#include "Novice.h"

class EnemyA : public Enemy {
public:
    EnemyA(const Vector2& position, const Vector2& velocity, float radius)
        : Enemy(position, velocity, radius) {}

    void Update() override {
        this->position_ = this->position_ + this->velocity_;
        if (this->position_.x < radius_) {
            this->position_.x = radius_;
            this->velocity_.x *= -1;
        } else if (this->position_.x > 1280 - radius_) {
            this->position_.x = 1280 - radius_;
            this->velocity_.x *= -1;
        }
    }

    void Draw() override {
        Novice::DrawEllipse(
            static_cast<int>(this->position_.x), 
            static_cast<int>(this->position_.y), 
            static_cast<int>(this->radius_), 
            static_cast<int>(this->radius_),
            0.0f,
            WHITE, 
            kFillModeSolid
        );
    }
};