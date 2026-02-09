#include <Novice.h>
#include "EventBus.hpp"
#include "SceneManager.hpp"
#include "Math.hpp"

const char kWindowTitle[] = "GC1C_12_ラ_ケツブン";


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    // ライブラリの初期化
    Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

    EventBus bus;
    SceneManager sceneManager(bus);

    sceneManager.Start(SceneID::Title);

    // ウィンドウの×ボタンが押されるまでループ
    while (Novice::ProcessMessage() == 0 && sceneManager.IsRunning()) {
        // フレームの開始
        Novice::BeginFrame();

        
        sceneManager.Render();
        sceneManager.Update();
        sceneManager.ApplyPending();

        // フレームの終了
        Novice::EndFrame();

    }

    // ライブラリの終了
    Novice::Finalize();
    return 0;
}


