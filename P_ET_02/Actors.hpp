#pragma once

#include <vector>
#include <Novice.h>
#include "Math.hpp"


namespace Actors {

    // =========================
    // Object
    // =========================

    class Box {
    public:
        Box(Math::Vector2 position, Math::Vector2 size, unsigned int color)
            : position(position), size(size), color(color) {
        }
        Math::Vector2 position; // center
        Math::Vector2 size;     // w/h
        unsigned int color;
    };

    class Ball {
    public:
        Ball(Math::Vector2 position, Math::Vector2 velocity, float radius, float mass, unsigned int color, int leftTime)
            : position(position), velocity(velocity), radius(radius), mass(mass), color(color), leftTime(leftTime) {
        }
        Math::Vector2 position;
        Math::Vector2 velocity;
        float radius;
        float mass;
        unsigned int color;
        int leftTime;
    };

    class EnemyBall {
    public:
        EnemyBall(Ball ball, bool isActive)
            : ball(ball), isActive(isActive) {
        }
        Ball ball;
        bool isActive;
        

    public: 
        void Draw() const {
            if (!isActive) return;
            Novice::DrawEllipse(
                static_cast<int>(ball.position.x),
                static_cast<int>(ball.position.y),
                static_cast<int>(ball.radius),
                static_cast<int>(ball.radius),
                0.0f,
                ball.color,
                kFillModeSolid
            );
        }

        void EnemyChasePlayer(
            Math::Vector2  playerPos,        // プレイヤー位置
            float speed,            // 移動速度（units/sec）
            float dt,               // デルタタイム（sec）
            float stopDistance      // これ以内なら止まる
        ) {
            Math::Vector2 toPlayer = playerPos - ball.position;
            float distSq = toPlayer.Len();
            float stopSq = stopDistance * stopDistance;

            // 近すぎる/同一点なら移動しない
            if (distSq <= stopSq || distSq < 1e-8f) {
                return;
            }

            float dist = sqrtf(distSq);
            Math::Vector2 dir = { toPlayer.x / dist, toPlayer.y / dist }; // 正規化

            // 今フレームで進む距離
            float step = speed * dt;

            // 行き過ぎ防止（プレイヤーを飛び越えない）
            float remain = dist - stopDistance;
            if (step > remain) step = remain;

            ball.position = (ball.position + (dir * step));
        }
    };

    class BulletShot {
    public:
        BulletShot(const Ball& ball, bool isActive)
            : ball(ball), isActive(isActive) {
        }
        Ball ball;
        bool isActive;
        

    public:
        void Draw() const {
            if (!isActive) return;
            Novice::DrawEllipse(
                static_cast<int>(ball.position.x),
                static_cast<int>(ball.position.y),
                static_cast<int>(ball.radius),
                static_cast<int>(ball.radius),
                0.0f,
                ball.color,
                kFillModeSolid
            );
        }

    };
    
    class Tank {
    public:
        Tank(Box box, Ball ball, Math::Vector2 sight, bool isShooting, int score, int shotCooldown)
            : box(box), ball(ball), sight(sight), isShooting(isShooting), score(score), shotCooldown(shotCooldown) {}
        Box box;
        Ball ball;
        Math::Vector2 sight;
        bool isShooting;
        int score;
        int shotCooldown;
        int health = 3;
        std::vector<Actors::BulletShot> bulletShots;

    public:
        void Move(Math::Vector2 delta, Math::Vector2 mouse) {
            box.position = box.position + delta;
            ball.position = ball.position + delta;
            sight = GetPointOnCircleEdge_(ball.position, ball.radius, mouse);
        }

        void Shot() {
            isShooting = true;

        }

        void Draw() const {
            Novice::DrawBox(
                static_cast<int>(box.position.x - box.size.x / 2),
                static_cast<int>(box.position.y - box.size.y / 2),
                static_cast<int>(box.size.x),
                static_cast<int>(box.size.y),
                0,
                box.color,
                kFillModeSolid
            );
            Novice::DrawEllipse(
                static_cast<int>(ball.position.x),
                static_cast<int>(ball.position.y),
                static_cast<int>(ball.radius),
                static_cast<int>(ball.radius),
                0.0f,
                ball.color,
                kFillModeSolid
            );
            Novice::DrawLine(
                static_cast<int>(ball.position.x),
                static_cast<int>(ball.position.y),
                static_cast<int>(sight.x),
                static_cast<int>(sight.y),
                WHITE
            );

            // show Hp
            Novice::ScreenPrintf(
                static_cast<int>(box.position.x - box.size.x / 2),
                static_cast<int>(box.position.y - box.size.y / 2 - 20),
                "HP: %d",
                health
            );
        }
    private:
        Math::Vector2 GetPointOnCircleEdge_(Math::Vector2 center, float radius, Math::Vector2 mouse) {
            float angle = atan2f(mouse.y - center.y, mouse.x - center.x);
            Math::Vector2 p;
            p.x = center.x + cosf(angle) * radius;
            p.y = center.y + sinf(angle) * radius;
            return p;
        }
    };



    
}