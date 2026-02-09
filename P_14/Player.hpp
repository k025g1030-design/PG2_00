#pragma once
#include <stdio.h>
#include <stdlib.h>

struct Vector2 {
	float x;
	float y;
};

struct Transform {
	Vector2 posi;
    float radius;
};

class Player {
public:
	explicit Player(Transform tf, int speed) : transform_(tf), speed_(speed) {}
	~Player() {}

	void Move(char* keys);
	void Draw();

private:
	Transform transform_;
	int speed_;
};