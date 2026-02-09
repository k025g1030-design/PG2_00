#pragma once 
#include "Math.hpp"

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
  
    void Update();
    void Draw();

private:
    Vector2 pos_;
    Vector2 vel_;
    int radius_;
    bool isAlive_;
    float aliveTime_;


};