#pragma once

#include "Novice.h"

namespace Game {
    class Enemy {
    public:
        Enemy(int posX, int posY, int speedX, int speedY, int radius) : posX_(posX), posY_(posY), speedX_(speedX), speedY_(speedY), radius_(radius) {}
        void Move();
        void Draw();

    private:
        int posX_;
        int posY_;
        int speedX_;
        int speedY_;
        int radius_;
    };
 
}  // namespace Enemy