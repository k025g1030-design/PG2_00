#pragma once 

#include <vector>
#include "Math.hpp"
#include "Bullet.hpp"

class Player {
public:
	explicit Player(Vector2 pos, Vector2 vel, int radius, bool isShot, int count) : pos_(pos), vel_(vel), radius_(radius), isShot_(isShot) {
		bullets_.assign(count, Bullet(
			pos,
			vel,
			radius / 2,
			false
		));
		coolDown_ = 0;
	};
	~Player() = default;
	void SetPosition(Vector2 pos) {
		pos_ = pos;
	}
	void SetVelocity(Vector2 vel) {
		vel_ = vel;
	}
	std::vector<Bullet>& GetBullets() {
		return bullets_;
	}
	void SetCoolDown(int coolDown) {
		coolDown_ = coolDown;
	}
	int GetCoolDown() {
		return coolDown_;
	}
	void Input(char* keys, char* preKeys);
	void Update();
	void Draw();

private:
	Vector2 pos_;
	Vector2 vel_;
	Vector2 input_;
	int radius_;

	std::vector<Bullet>	bullets_;
	int coolDown_;

	bool isShot_;
};

