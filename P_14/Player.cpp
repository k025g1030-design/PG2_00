#include "Player.hpp"
#include <Novice.h>

void Player::Move(char* keys) {
    if (keys[DIK_W]) {
        transform_.posi.y -= speed_;
    }
    if (keys[DIK_S]) {
        transform_.posi.y += speed_;
    }
    if (keys[DIK_A]) {
        transform_.posi.x -= speed_;
    }
    if (keys[DIK_D]) {
        transform_.posi.x += speed_;
    }
}

void Player::Draw() {
    Novice::DrawEllipse(
        static_cast<int>(transform_.posi.x),
        static_cast<int>(transform_.posi.y),
        static_cast<int>(transform_.radius),
        static_cast<int>(transform_.radius),
        0,
        WHITE,
        kFillModeSolid
    );
}
  