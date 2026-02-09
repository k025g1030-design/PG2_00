#pragma once
#include <memory>
#include "IScene.hpp"
#include "SceneTypes.hpp"

class SceneManager {
public:
    explicit SceneManager(EventBus& bus);

    void Start(SceneID initial);
    void Update();
    void Render() const;
    void ApplyPending();

    bool IsRunning() const;

private:
    std::unique_ptr<IScene> CreateScene_(SceneID id);
    void ChangeNow_(SceneID next);

private:
    EventBus& bus_;
    std::unique_ptr<IScene> current_;

    SceneID pendingScene_ = SceneID::Title;
    bool hasPending_ = false;
    bool running_ = true;
};
