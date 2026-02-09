#include <Novice.h>
#include "Player.hpp"

const char kWindowTitle[] = "GC1C_12_ラ_ケツブン";

/**
 * [確認課題] 10-1. メンバ変数と構造体
 */

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    // ライブラリの初期化
    Novice::Initialize(kWindowTitle, 1280, 720);

    // キー入力結果を受け取る箱
    char keys[256] = {0};
    char preKeys[256] = {0};
               
    Player* player = new Player({ { 640.0f, 360.0f }, 50.0f }, 5);



    // ウィンドウの×ボタンが押されるまでループ
    while (Novice::ProcessMessage() == 0) {
        // フレームの開始
        Novice::BeginFrame();

        
        // キー入力を受け取る
        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        player->Move(keys);

        player->Draw();

        // フレームの終了
        Novice::EndFrame();

        // ESCキーが押されたらループを抜ける
        if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
            break;
        }
    }

    delete player;

    // ライブラリの終了
    Novice::Finalize();
    return 0;
}


