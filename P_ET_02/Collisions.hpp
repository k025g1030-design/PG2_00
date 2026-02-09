#pragma once

#include "Math.hpp"
#include "Actors.hpp"
#include "PhysicsForces.hpp"

namespace Collision {
    // =========================
    // Collision
    // =========================
    bool CircleAABB(
        const Math::Vector2& c, 
        float r,
        const Math::Vector2& boxCenter, 
        const Math::Vector2& boxSize,

        Math::Vector2& outNormal, float& outPenetration
    ) {
        Math::Vector2 half{ boxSize.x * 0.5f, boxSize.y * 0.5f };
        Math::Vector2 min{ boxCenter.x - half.x, boxCenter.y - half.y };
        Math::Vector2 max{ boxCenter.x + half.x, boxCenter.y + half.y };

        Math::Vector2 closest{
            std::clamp(c.x, min.x, max.x),
            std::clamp(c.y, min.y, max.y)
        };

        Math::Vector2 d = c - closest;
        float dist2 = d.x * d.x + d.y * d.y;
        if (dist2 > r * r) return false;

        float dist = std::sqrtf(dist2);
        if (dist > 1e-6f) {
            outNormal = { d.x / dist, d.y / dist };
            outPenetration = r - dist;
            return true;
        }

        // inside: minimal push dir
        float leftPen = (c.x - min.x);
        float rightPen = (max.x - c.x);
        float bottomPen = (c.y - min.y);
        float topPen = (max.y - c.y);

        float minPen = leftPen; outNormal = { +1, 0 };
        if (rightPen < minPen) { minPen = rightPen;  outNormal = { -1, 0 }; }
        if (bottomPen < minPen) { minPen = bottomPen; outNormal = { 0, +1 }; }
        if (topPen < minPen) { minPen = topPen;    outNormal = { 0, -1 }; }

        outPenetration = r;
        return true;
    }

    bool ResolveBallBall(Actors::Ball& a, Actors::Ball& b, const Physics::PhysicsForces& p) {
        Math::Vector2 delta = b.position - a.position;
        float dist = delta.Len();
        float rSum = a.radius + b.radius;
        if (dist >= rSum) return false;

        Math::Vector2 n = (dist > 1e-6f) ? Math::Vector2{ delta.x / dist, delta.y / dist } : Math::Vector2{ 1.0f, 0.0f };
        float penetration = rSum - dist;

        float invMa = (a.mass > 0.0f) ? 1.0f / a.mass : 0.0f;
        float invMb = (b.mass > 0.0f) ? 1.0f / b.mass : 0.0f;
        float invSum = invMa + invMb;

        // position correction
        if (invSum > 0.0f) {
            float corrMag = (max(penetration - p.penetrationSlop, 0.0f) / invSum) * p.correctionPercent;
            Math::Vector2 corr = n * corrMag;
            a.position = (a.position - (corr * invMa));
            b.position = (b.position + (corr * invMb));
        }

        Math::Vector2 rv = (b.velocity - a.velocity);
        float velAlongNormal = rv.Dot( n);
        if (velAlongNormal > 0.0f) return true;

        float e = p.restitutionBall;
        float j = -(1.0f + e) * velAlongNormal;
        if (invSum > 0.0f) j /= invSum;

        Math::Vector2 impulse = (n * j);
        a.velocity = (a.velocity - (impulse * invMa));
        b.velocity = (b.velocity + (impulse * invMb));

        return true;
    }

}