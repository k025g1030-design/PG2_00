#pragma once

namespace {
    const char kWindowTitle[] = "4x4 Camera Matrix Demo (2 Balls + Drag + Friction + Resting)";
    const int kWindowWidth = 1280;
    const int kWindowHeight = 720;

    const int kMaxTrail = 100;
    const int kMaxPredict = 100;

    const int kMaxEnemyLeftTime = 600; // 10秒
    const int kMaxBulletLeftTime = 180; // 3秒

    const int kPlayerMoveSpeed = 6;

    const int kMaxMagazine = 5;
    const int kMaxShotCooldown = 30; // 0.5秒

    const int kEnemySpawnTime = 120; // 2秒
    const int kEnemySpawnCountMax = 5;
}