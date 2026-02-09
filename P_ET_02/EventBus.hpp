#pragma once
#include <functional>
#include <utility>
#include <vector>
#include "SceneTypes.hpp"

class EventBus {
public:
    using SceneChangeHandler = std::function<void(const SceneChangeEvent&)>;

    void SubscribeSceneChange(SceneChangeHandler handler) {
        sceneChangeHandlers_.push_back(std::move(handler));
    }

    void Publish(const SceneChangeEvent& ev) {
        for (auto& h : sceneChangeHandlers_) {
            h(ev);
        }
    }

private:
    std::vector<SceneChangeHandler> sceneChangeHandlers_;
};
