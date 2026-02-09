/**
 * [確認課題]PG2_3-1. 関数と引数アドレス 
 **/
#include <Novice.h>
#include <math.h>

const char kWindowTitle[] = "GC1C_12_ラ_ケツブン";
const int kWinWidth = 1280;
const int kWinHeight = 720;
const int SPEED = 5;
const int PLAYER_WIDTH = 20;

struct Vector2 {
    float x;
    float y;
};

struct Player {
    Vector2 posi;
    Vector2 size;
    bool isLeft;
};

void DetectFrontier(Vector2* posi) {
    posi->x = min(kWinWidth - PLAYER_WIDTH, max(PLAYER_WIDTH, posi->x));
    posi->y = min(kWinHeight - PLAYER_WIDTH, max(PLAYER_WIDTH, posi->y));
}

void AutoMove(Player* player) {
    if (player->isLeft) {
        player->posi.x += SPEED;
        if (player->posi.x > kWinWidth - player->size.x) {
            player->isLeft = !player->isLeft;
        }
    } else {
        player->posi.x -= SPEED;
        if (player->posi.x < player->size.x) {
            player->isLeft = !player->isLeft;
        }
    }
}


void Move(Vector2* posi) {
    Vector2 input = { 0, 0 };
    if (Novice::CheckHitKey(DIK_W) || Novice::CheckHitKey(DIK_UP)) {
        input.y -= 1;
    }
    if (Novice::CheckHitKey(DIK_D) || Novice::CheckHitKey(DIK_RIGHT)) {
        input.x += 1;
    }
    if (Novice::CheckHitKey(DIK_A) || Novice::CheckHitKey(DIK_LEFT)) {
        input.x -= 1;
    }
    if (Novice::CheckHitKey(DIK_S) || Novice::CheckHitKey(DIK_DOWN)) {
        input.y += 1;
    }

    if ((input.x != 0 || input.y != 0)) {
        double angle = atan2(input.y, input.x);

        posi->x += (float)(cos(angle) * SPEED);
        posi->y += (float)(sin(angle) * SPEED);

        // 辺界
        DetectFrontier(posi);
    }
}

void RenderPlayer(const Vector2* posi) {
    Novice::DrawEllipse((int)posi->x, (int)posi->y, PLAYER_WIDTH,
                    PLAYER_WIDTH, 0.0f, 0xFFFFFFFF, kFillModeSolid);
}




// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    // ライブラリの初期化
    Novice::Initialize(kWindowTitle, 1280, 720);

    Player player = {
        { kWinWidth / 2.0f, kWinHeight / 2.0f },
        { PLAYER_WIDTH, PLAYER_WIDTH },
        true,
    };

    // キー入力結果を受け取る箱
    char keys[256] = {0};
    char preKeys[256] = {0};


    // ウィンドウの×ボタンが押されるまでループ
    while (Novice::ProcessMessage() == 0) {
        // フレームの開始
        Novice::BeginFrame();

        
        

        Move(&player.posi);

        AutoMove(&player);

        RenderPlayer(&player.posi);

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


