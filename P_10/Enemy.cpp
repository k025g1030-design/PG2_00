#include "Enemy.hpp"

namespace Game {
    void Enemy::Move() {
        posX_ += speedX_;
        posY_ += speedY_;
        // 画面端で跳ね返る処理
        if (posX_ < radius_ || posX_ > 1280 - radius_) {
            speedX_ = -speedX_;
        }
        if (posY_ < radius_ || posY_ > 720 - radius_) {
            speedY_ = -speedY_;
        }
    }
    void Enemy::Draw() {
        Novice::DrawEllipse(posX_, posY_, radius_, radius_, 0, WHITE, kFillModeSolid);
    }
}  // namespace Game