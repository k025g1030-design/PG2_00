#pragma once

#include "Math.hpp"
#include "Actors.hpp"

namespace Physics {
    struct PhysicsForces {
        float gravityY = -100.0f;        // +Y上
        float inputForceX = 1200.0f;     // 入力は「力」(a=F/m)

        // 空気抵抗（力）：F = -c1 v - c2 |v| v
        float dragLinear = 0.20f;
        float dragQuadratic = 0.009f;

        // 摩擦（支持接触時）：|Δvt| = μ|g|dt（簡易）
        float frictionMu = 0.05f;

        float restitutionWall = 0.90f;

        float restitutionBall = 0.99f;

        // 小さい法線速度は「跳ねない」
        float restVelThreshold = 100.0f;

        int subSteps = 4;

        // 位置補正（球同士）
        float penetrationSlop = 0.01f;
        float correctionPercent = 0.80f;

        // 予測設定
        int predictSteps = 4 * 60;         // 4秒先（60fps想定）
        int predictIntervalFrames = 2;  // 何フレーム毎に予測更新するか
    };

    // =========================
    // Forces
    // =========================
    Math::Vector2 ComputeDragForce(const Math::Vector2 velocity, const PhysicsForces& p) {
        float speed = velocity.Len();
        // F = -c1 v - c2 |v| v
        return {
            -p.dragLinear * velocity.x - p.dragQuadratic * speed * velocity.x,
            -p.dragLinear * velocity.y - p.dragQuadratic * speed * velocity.y
        };
    }

    Math::Vector2 ComputeDragForce(const Actors::Ball& ball, const PhysicsForces& p) {
        return ComputeDragForce(ball.velocity, p);
    }

    void ApplySurfaceFriction(Math::Vector2& velocity, const PhysicsForces& p, float dt, bool onSurfaceUp) {
        if (!onSurfaceUp) return;

        float dv = p.frictionMu * std::abs(p.gravityY) * dt;
        float vx = velocity.x;
        float avx = std::abs(vx);

        if (avx <= dv) {
            velocity.x = 0.0f;
        } else {
            velocity.x = vx - (vx > 0 ? dv : -dv);
        }
    }

    void ApplySurfaceFriction(Actors::Ball& ball, const PhysicsForces& p, float dt, bool onSurfaceUp) {
        ApplySurfaceFriction(ball.velocity, p, dt, onSurfaceUp);
    }




   

    



}