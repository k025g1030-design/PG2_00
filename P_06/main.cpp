#include <Novice.h>

const char kWindowTitle[] = "GC1C_12_ラ_ケツブン";

const int SPEED = 5;

struct Vector2 {
    float x;
    float y;
};

void PlayMove(Vector2* posi, char* keys) {
    if (keys[DIK_W] != 0) {
        posi->y -= SPEED;
    } 
    if (keys[DIK_S] != 0) {
        posi->y += SPEED;
    }
    if (keys[DIK_A] != 0) {
        posi->x -= SPEED;
    }
    if (keys[DIK_D] != 0) {
        posi->x += SPEED;
    }
}


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    // ライブラリの初期化
    Novice::Initialize(kWindowTitle, 1280, 720);

    Vector2 playerPosi = { 640.0f, 360.0f };

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


        PlayMove(&playerPosi, keys);

        // 描画処理ここから
        Novice::DrawBox(static_cast<int>(playerPosi.x) - 25,
                        static_cast<int>(playerPosi.y) - 25,
                        50,
                        50,
                        0.0f,
                        WHITE,
            kFillModeSolid);

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


