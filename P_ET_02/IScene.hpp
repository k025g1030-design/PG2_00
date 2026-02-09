#pragma once
#include "EventBus.hpp"

class IScene {
public:
    virtual ~IScene() = default;

    virtual void OnEnter() {}
    virtual void OnExit() {}

    virtual void Render() const = 0;
    virtual void Update(EventBus& bus) = 0;
    virtual const char* Name() const = 0;
};
