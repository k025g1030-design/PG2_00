#include "Enemy.hpp"
#include <stdio.h>     

void Enemy::ShowStatus() {
    printf("[%s]=> HP: %d 残る\n", name_, hp_);
}

void Enemy::Damage(int damage) {
    hp_ -= damage;
    if (hp_ < 0) {
        hp_ = 0;
    }
    printf("[%s] に [%d] 点ダメージをしました。HP: %d 残る\n", name_, damage, hp_);
}

void Enemy::EmotionalDamage(char* text) {
    
}