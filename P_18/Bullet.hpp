#pragma once 
#include "Math.hpp"
#include "Enemy.hpp"

class Bullet {
public:
    explicit Bullet(Vector2 pos, Vector2 vel, int radius, bool isAlive) : pos_(pos), vel_(vel), radius_(radius), isAlive_(isAlive) { 
        aliveTime_ = 1.0f; 
        
    };
    ~Bullet() = default;


    void SetPosition(Vector2 pos) {
        pos_ = pos;
    }
    void SetVelocity(Vector2 vel) {
        vel_ = vel;
    }
    bool IsAlive() {
        return isAlive_;
    }
    void SetAlive(bool alive) {
        isAlive_ = alive;
    }
  
    bool ResolveBallBall(Enemy& enemy) {
        if (!isAlive_) {
            return false;
        }
        float dx = pos_.x - enemy.GetPosition().x;
        float dy = pos_.y - enemy.GetPosition().y;
        float distanceSquared = dx * dx + dy * dy;
        //float radiusSum = radius_ + enemy.GetRadius();
        float radiusSum = static_cast<float>(radius_) + enemy.GetRadius();

        return distanceSquared <= radiusSum * radiusSum;

    }

    void Update();
    void Draw();

private:
    Vector2 pos_;
    Vector2 vel_;
    int radius_;
    bool isAlive_;
    float aliveTime_;


};