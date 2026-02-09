#pragma once
#include "IScene.hpp"
#include "Actors.hpp"
#include "Math.hpp"
#include "Button.hpp"

class GameScene final : public IScene {
public:
    void OnEnter() override;
    void OnExit() override;
    void Render() const override;
    void Update(EventBus& bus) override;
    const char* Name() const override;

private:
    Component::Button escButton_;
    bool prevMouseDown_{ false };
    int frameCounter_ = 0;


private:
    Actors::Tank* player_;

    std::vector<Actors::EnemyBall> enemyBalls_;
};
