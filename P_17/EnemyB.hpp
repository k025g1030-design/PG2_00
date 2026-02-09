#pragma once

#include "Enemy.hpp"
#include "Novice.h"

class EnemyB : public Enemy {
public:
    EnemyB(const Vector2& position, const Vector2& velocity, float radius)
        : Enemy(position, velocity, radius) {
    }

    void Update() override {
        this->position_ = this->position_ + this->velocity_;
        if (this->position_.y < radius_) {
            this->position_.y = radius_;
            this->velocity_.y *= -1;
        } else if (this->position_.y > 720 - radius_) {
            this->position_.y = 720 - radius_;
            this->velocity_.y *= -1;
        }
    }

    void Draw() override {
        Novice::DrawEllipse(
            static_cast<int>(this->position_.x),
            static_cast<int>(this->position_.y),
            static_cast<int>(this->radius_),
            static_cast<int>(this->radius_),
            0.0f,
            RED,
            kFillModeSolid
        );
    }
};