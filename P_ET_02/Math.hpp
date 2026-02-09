#pragma once

#include <cmath>
#include <algorithm>

const static int kWindowWidth = 1280;
const static int kWindowHeight = 720;
const static float moveSpeed = 4.0f;


const static int kMaxBulletLeftTime = 180;
const static int kMaxEnemyLeftTime = 600; // 10秒

const static int kMaxMagazine = 5;
const static int kMaxShotCooldown = 30; // 0.5秒

const static int kEnemySpawnTime = 240; // 
const static int kEnemySpawnCountMax = 10;


namespace Math {


    struct Matrix4x4 {
        float m[4][4];

        Matrix4x4 operator*(const Matrix4x4& other) const {
            Matrix4x4 R{};
            for (int row = 0; row < 4; ++row) {
                for (int col = 0; col < 4; ++col) {
                    for (int k = 0; k < 4; ++k) {
                        R.m[row][col] += m[row][k] * other.m[k][col];
                    }
                }
            }
            return R;
        }

        Matrix4x4 MakeIdentity() {
            Matrix4x4 r{};
            r.m[0][0] = 1.0f; r.m[1][1] = 1.0f; r.m[2][2] = 1.0f; r.m[3][3] = 1.0f;
            return r;
        }

        Matrix4x4 MakeTranslateMatrix(float tx, float ty, float tz = 0.0f) {
            Matrix4x4 r = MakeIdentity();
            // 行ベクトル方式なので平行移動は row=3 に入る
            r.m[3][0] = tx;
            r.m[3][1] = ty;
            r.m[3][2] = tz;
            return r;
        }

        // Ortho: World -> NDC (x:[l,r]->[-1,1], y:[b,t]->[-1,1])
        Matrix4x4 MakeOrthographicMatrix(float left, float right, float top, float bottom) {
            Matrix4x4 r{};
            r.m[0][0] = 2.0f / (right - left);
            r.m[1][1] = 2.0f / (top - bottom);
            r.m[2][2] = 1.0f;
            r.m[3][3] = 1.0f;

            r.m[3][0] = -(right + left) / (right - left);
            r.m[3][1] = -(top + bottom) / (top - bottom);
            return r;
        }

        // Viewport: NDC -> Screen（Y反転）
        Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height) {
            Matrix4x4 r = MakeIdentity();
            r.m[0][0] = width / 2.0f;
            r.m[1][1] = -height / 2.0f;
            r.m[3][0] = left + width / 2.0f;
            r.m[3][1] = top + height / 2.0f;
            return r;
        }
    };

    struct Vector2 { 
        float x, y; 

        Vector2 operator+(const Vector2& other) const {
            return Vector2(x + other.x, y + other.y);
        }
        Vector2 operator-(const Vector2& other) const {
            return Vector2(x - other.x, y - other.y);
        }
        Vector2 operator*(const float& other) const {
            return Vector2(x * other, y * other);
        }

        float Dot(const Vector2& other) const {
            return x * other.x + y * other.y;
        }

        float Len() const {
            return std::sqrtf(x * x + y * y);
        }

        Vector2 Normalize() {
            float l = Len();
            if (l <= 1e-6f) return { 1.0f, 0.0f };
            return { x / l, y / l };
        }

        Vector2 TransformPoint2D(const Matrix4x4& m4x4) const {
            // z=0, w=1
            float rx = x * m4x4.m[0][0] + y * m4x4.m[1][0] + 0.0f * m4x4.m[2][0] + 1.0f * m4x4.m[3][0];
            float ry = x * m4x4.m[0][1] + y * m4x4.m[1][1] + 0.0f * m4x4.m[2][1] + 1.0f * m4x4.m[3][1];
            return { rx, ry };
        }

        // v' = v - (1+e)(v·n)n
        Vector2 Reflect(Vector2 n, float e) const {
            float d = this->Dot(n);
            return { x - (1.0f + e) * d * n.x, y - (1.0f + e) * d * n.y };
        }

        // 支持接触：法線方向の食い込み速度だけ消す
        void CancelNormalVelocity( Vector2 n) {
            float vn = this->Dot(n);
            if (vn < 0.0f) {
                x -= vn * n.x;
                y -= vn * n.y;
            }
        }
    };
    

}