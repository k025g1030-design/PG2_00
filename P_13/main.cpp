#include <stdio.h>
#include <stdlib.h>
#include "Enemy.hpp"
#include <cstdint>

/*
[確認課題]PG2_9-2. コンストラクタ・デストラクタ
*/

int fastRandInt(int min, int max) {
    static uint64_t x = 0x123456789ABCDEF;
    x ^= x << 7;
    x ^= x >> 9;
    uint64_t r = x * 2685821657736338717ULL;
    return min + (r % (max - min + 1));
}


int main() {
    Enemy* enemy = new Enemy(100, (char*)"Goblin");

    while (!enemy->IsDead()) {
        enemy->Damage(fastRandInt(0, 15));
        enemy->ShowStatus();
    }

    delete enemy;
    
    return 0;
}