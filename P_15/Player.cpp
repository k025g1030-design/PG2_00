#include <Novice.h>
#include "Player.hpp"
#include "Math.hpp"
#include <cmath>

void Player::Input(char* keys, char* preKeys) {
    input_ = {0,0};
    if (keys[DIK_W] != 0) {
        input_.y = -1;
    } else if (keys[DIK_S] != 0) {
        input_.y = 1;
    }
    if (keys[DIK_A] != 0) {
        input_.x = -1;
    } else if (keys[DIK_D] != 0) {
        input_.x = 1;
    }
    if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_SPACE] != 0) {
        isShot_ = true;
    } 

}

void Player::Update() {
    if (isShot_ && coolDown_ == 0) {
        isShot_ = false;
        for (auto& b : bullets_) {
            if (!b.IsAlive()) {
                b.SetAlive(true);
                b.SetPosition(pos_);
                break;
            }
        }
        coolDown_ = COOL_DOWN;
    }
    if (coolDown_ > 0) {
        coolDown_--;
        if (coolDown_ < 0) {
            coolDown_ = 0;
        }
    }

    double angle = atan2(input_.y, input_.x);

    if (input_.x != 0 || input_.y != 0) {
        vel_ = {
            static_cast<float>(cos(angle) * SPEED),
            static_cast<float>(sin(angle) * SPEED)
        };
        pos_.x += vel_.x;
        pos_.y += vel_.y;

                           
        // 辺界
        pos_.x = min(kWindowWidth - radius_, max(radius_, pos_.x));
        pos_.y = min(kWindowHeight - radius_, max(radius_, pos_.y));
    }


}

void Player::Draw() {
    Novice::DrawEllipse((int)pos_.x, (int)pos_.y, radius_, radius_, 0 , WHITE, kFillModeSolid);

}