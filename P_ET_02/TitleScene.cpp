#include <iostream>
#include "TitleScene.hpp"
#include "Input.hpp"
#include "SceneTypes.hpp"
#include "Math.hpp"

void TitleScene::OnEnter() {
    startButton_ = Component::Button({ 160, 30 }, { kWindowWidth / 2 - 80, kWindowHeight / 2 + 140 }, "START");
    exitButton_ = Component::Button({ 160, 30 }, { kWindowWidth / 2 - 80, kWindowHeight / 2 + 180 }, "EXIT");

    titleText_ = Component::TextSpan({ 400, 60 }, { kWindowWidth / 2 - 200, kWindowHeight / 2 - 100 }, "GP2 ET Game");
}

void TitleScene::OnExit() {
    std::cout << "[Exit ] TitleScene\n";
}

void TitleScene::Render() const {
    titleText_.Render();
    startButton_.Render();
    exitButton_.Render();
}

void TitleScene::Update(EventBus& bus) {

    // メニューシーンの更新処理をここに追加
    bool mouseDown = Novice::IsPressMouse(0);
    int moX = 0;
    int moY = 0;
    Novice::GetMousePosition(&moX, &moY);
    if (startButton_.HandleMouse(moX, moY, mouseDown, prevMouseDown_)) {
        bus.Publish(SceneChangeEvent{ SceneID::Game });
    } else if (exitButton_.HandleMouse(moX, moY, mouseDown, prevMouseDown_)) {
        bus.Publish(SceneChangeEvent{ SceneID::Exit });
    }
    prevMouseDown_ = mouseDown;
}

const char* TitleScene::Name() const {
    return "TitleScene";
}
