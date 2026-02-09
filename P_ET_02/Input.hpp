#pragma once

#include <Novice.h>
#include "Math.hpp"


inline Math::Vector2 ReadCommand() {
    Math::Vector2 input{ 0.0f, 0.0f };
    if (Novice::CheckHitKey(DIK_W)) {
        input.y -= 1.0f;   
    } else if (Novice::CheckHitKey(DIK_S)) {
        input.y += 1.0f;
    }
    if (Novice::CheckHitKey(DIK_A)) {
        input.x -= 1.0f;
    } else if (Novice::CheckHitKey(DIK_D)) {
        input.x += 1.0f;
    }  
    return input;
    
}