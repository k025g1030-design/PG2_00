#pragma once

#include <Novice.h>
#include <vector>

#include "Math.hpp"
#include "Actors.hpp"


namespace Render {
    // =========================
    // Drawing
    // =========================
    void DrawWorldBounds(const Math::Vector2& mn, const Math::Vector2& mx, const Math::Matrix4x4& camM) {
        Math::Vector2 ltW{ mn.x, mx.y }, rtW{ mx.x, mx.y }, lbW{ mn.x, mn.y }, rbW{ mx.x, mn.y };
        Math::Vector2 lt = ltW.TransformPoint2D(camM);
        Math::Vector2 rt = rtW.TransformPoint2D(camM);
        Math::Vector2 lb = lbW.TransformPoint2D(camM);
        Math::Vector2 rb = rbW.TransformPoint2D(camM);
        unsigned int c = 0x8080FFFF;
        Novice::DrawLine((int)lt.x, (int)lt.y, (int)rt.x, (int)rt.y, c);
        Novice::DrawLine((int)rt.x, (int)rt.y, (int)rb.x, (int)rb.y, c);
        Novice::DrawLine((int)rb.x, (int)rb.y, (int)lb.x, (int)lb.y, c);
        Novice::DrawLine((int)lb.x, (int)lb.y, (int)lt.x, (int)lt.y, c);
    }

    void DrawAABBWorld(const Actors::Box& box, const Math::Matrix4x4& camM) {
        Math::Vector2 half{ box.size.x * 0.5f, box.size.y * 0.5f };
        Math::Vector2 ltW{ box.position.x - half.x, box.position.y + half.y };
        Math::Vector2 rtW{ box.position.x + half.x, box.position.y + half.y };
        Math::Vector2 lbW{ box.position.x - half.x, box.position.y - half.y };
        Math::Vector2 rbW{ box.position.x + half.x, box.position.y - half.y };
        Math::Vector2 lt = ltW.TransformPoint2D(camM);
        Math::Vector2 rt = rtW.TransformPoint2D(camM);
        Math::Vector2 lb = lbW.TransformPoint2D(camM);
        Math::Vector2 rb = rbW.TransformPoint2D(camM);
        Novice::DrawLine((int)lt.x, (int)lt.y, (int)rt.x, (int)rt.y, box.color);
        Novice::DrawLine((int)rt.x, (int)rt.y, (int)rb.x, (int)rb.y, box.color);
        Novice::DrawLine((int)rb.x, (int)rb.y, (int)lb.x, (int)lb.y, box.color);
        Novice::DrawLine((int)lb.x, (int)lb.y, (int)lt.x, (int)lt.y, box.color);
    }

    void DrawTrail(const std::vector<Math::Vector2>& trail, const Math::Matrix4x4& camM, unsigned int color) {
        for (int i = 0; i + 1 < (int)trail.size(); ++i) {
            Math::Vector2 a = trail[i].TransformPoint2D(camM);
            Math::Vector2 b = trail[i + 1].TransformPoint2D(camM);
            Novice::DrawLine((int)a.x, (int)a.y, (int)b.x, (int)b.y, color);
        }
    }

}