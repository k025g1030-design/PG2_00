#pragma once
#include <stdio.h>
#include <stdlib.h>

class Enemy {
public:
	explicit Enemy(int hp, char* name) : hp_(hp), name_(name) {}
	~Enemy() {
        printf("[%s]を倒れた!\n", name_);
	}

	void ShowStatus();
    void Damage(int damage);
	void EmotionalDamage(char* text);
	bool IsDead() const {
		return hp_ <= 0;
    }

private:  
	int hp_;
    char* name_;
};
