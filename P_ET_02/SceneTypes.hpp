#pragma once

enum class SceneID {
    Title,
    Game,
    Result,
    Exit
};

struct SceneChangeEvent {
    SceneID next;
};
