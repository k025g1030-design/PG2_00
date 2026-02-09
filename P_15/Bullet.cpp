#include <Novice.h>
#include "Bullet.hpp"
#include "Math.hpp"


void Bullet::Update() {
    
    if (aliveTime_ > 0) {
        aliveTime_ -= B_ALIVE;
    } else {
        aliveTime_ = 1.0f;
        isAlive_ = false;
    }
    pos_.y -= SPEED;
}

void Bullet::Draw() {
    Novice::DrawEllipse((int)pos_.x, (int)pos_.y, radius_, radius_, 0, RED, kFillModeSolid);
}