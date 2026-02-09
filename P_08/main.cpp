#include <Novice.h>

const char kWindowTitle[] = "GC1C_12_ラ_ケツブン";

const int SPEED = 5;

struct Vector2 {
    float x;
    float y;
};


struct Player {
    Vector2 posi;
    char keys[256];
    char preKeys[256];
};

Player InitializePlayer() {
    return Player{ { 640.0f, 360.0f }, { 0 }, { 0 }};
}

void PlayMove(Player* player) {
    if (player->keys[DIK_W] != 0) {
        player->posi.y -= SPEED;
    }
    if (player->keys[DIK_S] != 0) {
        player->posi.y += SPEED;
    }
    if (player->keys[DIK_A] != 0) {
        player->posi.x -= SPEED;
    }
    if (player->keys[DIK_D] != 0) {
        player->posi.x += SPEED;
    }

    Novice::DrawBox(static_cast<int>(player->posi.x) - 25,
        static_cast<int>(player->posi.y) - 25,
        50,
        50,
        0.0f,
        WHITE,
        kFillModeSolid);
}


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    // ライブラリの初期化
    Novice::Initialize(kWindowTitle, 1280, 720);

    Player player = InitializePlayer();

    // ウィンドウの×ボタンが押されるまでループ
    while (Novice::ProcessMessage() == 0) {
        // フレームの開始
        Novice::BeginFrame();


        // キー入力を受け取る
        memcpy(player.preKeys, player.keys, 256);
        Novice::GetHitKeyStateAll(player.keys);


        PlayMove(&player);


        // フレームの終了
        Novice::EndFrame();

        // ESCキーが押されたらループを抜ける
        if (player.preKeys[DIK_ESCAPE] == 0 && player.keys[DIK_ESCAPE] != 0) {
            break;
        }
    }

    // ライブラリの終了
    Novice::Finalize();
    return 0;
}


