#pragma once
#include "IScene.hpp"
#include "Button.hpp"     
#include "Text.hpp"

class TitleScene final : public IScene {
public:
    void OnEnter() override;
    void OnExit() override;
    void Render() const override;
    void Update(EventBus& bus) override;
    const char* Name() const override;

private:
    bool prevMouseDown_{ false };

private:
    Component::Button startButton_;
    Component::Button exitButton_;

    Component::TextSpan titleText_;

};
