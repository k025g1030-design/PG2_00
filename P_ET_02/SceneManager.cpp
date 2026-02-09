#include <iostream>
#include <memory>
#include "SceneManager.hpp"
#include "TitleScene.hpp"
#include "GameScene.hpp"

SceneManager::SceneManager(EventBus& bus) : bus_(bus) {
    bus_.SubscribeSceneChange([this](const SceneChangeEvent& ev) {
        // Update中は即切替しない（安全のため）
        pendingScene_ = ev.next;
        hasPending_ = true;
        });
}

void SceneManager::Start(SceneID initial) {
    ChangeNow_(initial);
}

void SceneManager::Update() {
    if (current_) {
        current_->Update(bus_);
    }
}

void SceneManager::Render() const {
    if (current_) {
        current_->Render();
    }
}

void SceneManager::ApplyPending() {
    if (!hasPending_) return;
    hasPending_ = false;
    ChangeNow_(pendingScene_);
}

bool SceneManager::IsRunning() const {
    return running_;
}

std::unique_ptr<IScene> SceneManager::CreateScene_(SceneID id) {
    switch (id) {
    case SceneID::Title:  return std::make_unique<TitleScene>();
    case SceneID::Game:   return std::make_unique<GameScene>();
   // case SceneID::Result: return std::make_unique<ResultScene>();
    case SceneID::Exit:   return nullptr;
    }
    return nullptr;
}

void SceneManager::ChangeNow_(SceneID next) {
    if (current_) {
        current_->OnExit();
        current_.reset();
    }

    if (next == SceneID::Exit) {
        running_ = false;
        std::cout << "[SceneManager] Exit requested.\n";
        return;
    }

    current_ = CreateScene_(next);
    if (!current_) {
        running_ = false;
        std::cout << "[SceneManager] Failed to create scene.\n";
        return;
    }

    current_->OnEnter();
}
