#include <Novice.h>
#include "EnemyA.hpp"
#include "EnemyB.hpp"

const char kWindowTitle[] = "GC1C_12_ラ_ケツブン";

/**
 * [確認課題]PG2_11-3. ポリモーフィズム
 */


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    // ライブラリの初期化
    Novice::Initialize(kWindowTitle, 1280, 720);

    EnemyA* enemyA = new EnemyA({ 640.0f, 360.0f }, { 2.0f, 0.0f }, 10.0f);
    EnemyB* enemyB = new EnemyB({ 640.0f, 360.0f }, { 0.0f, 3.0f }, 20.0f);
    

    // キー入力結果を受け取る箱
    char keys[256] = {0};
    char preKeys[256] = {0};

    // ウィンドウの×ボタンが押されるまでループ
    while (Novice::ProcessMessage() == 0) {
        // フレームの開始
        Novice::BeginFrame();

        
        // キー入力を受け取る
        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);


        enemyA->Update();
        enemyB->Update();

        enemyA->Draw();
        enemyB->Draw();

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


