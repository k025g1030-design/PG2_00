#include <Novice.h>
#include "Player.hpp"
#include "Bullet.hpp"


const char kWindowTitle[] = "GC1C_12_ラ_ケツブン";

void Input(Player* player, char* keys, char* preKeys) {
    player->Input(keys, preKeys);
}

void Update(Player* player) {
    player->Update();
    for (auto& b : player->GetBullets()) {
        if (b.IsAlive()) {
            b.Update();
        }
    }
}


void Render(Player* player) {
    player->Draw();
    for (auto b : player->GetBullets()) {
        if (b.IsAlive()) {
            b.Draw();
        }
    }
}

/**
 * [確認課題] 10-2. 包含
 */

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    // ライブラリの初期化
    Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);


    Player* player = new Player(
        { kWindowWidth / 2, kWindowHeight / 2},
        { 0, 0},
        30,
        false,
        10
    );

    // キー入力結果を受け取る箱
    char keys[256] = {0};
    char preKeys[256] = {0};

    // ウィンドウの×ボタンが押されるまでループ
    while (Novice::ProcessMessage() == 0) {

        // キー入力を受け取る
        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        Input(player, keys, preKeys);

        Update(player);

        // フレームの開始
        Novice::BeginFrame();
        
        Render(player);

        // フレームの終了
        Novice::EndFrame();

        // ESCキーが押されたらループを抜ける
        if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
            break;
        }
    }

    // ライブラリの終了
    Novice::Finalize();
    return 0;
}


