#pragma once
#include <string>
#include <Novice.h>
#include "Math.hpp"


namespace Component {
    class TextSpan {
    public:
        explicit TextSpan(Math::Vector2 size, Math::Vector2 position, std::string name, int value) : size_(size), position_(position), name_(name), value_(value) {}
        explicit TextSpan(Math::Vector2 size, Math::Vector2 position, std::string name) : size_(size), position_(position), name_(name) {}
        explicit TextSpan() {}

        void Render() const {
            if (!isVisible_) return;
            int x = static_cast<int>(position_.x);
            int y = static_cast<int>(position_.y);
            int w = static_cast<int>(size_.x);
            int h = static_cast<int>(size_.y);

            
            if (value_ == -1) {
                Novice::DrawBox(x, y, w, h, 0, 0x404040FF, kFillModeSolid);
                //Novice::DrawBox(x, y, w, h, 0, 0xFFFFFFFF, kFillModeWireFrame);
                Novice::ScreenPrintf(x + 10, y + h / 2 - 8, "%s", name_.c_str());
            } else {
                Novice::DrawSprite(x, y, value_, 1.0f, 1.0f, 0.0f, WHITE);
            }
            
            
        }

        void SetName(std::string name) {
            name_ = name;
        }
        std::string GetName() {
            return name_;
        }
        void SetSize(Math::Vector2 size) {
            size_ = size;
        }
        Math::Vector2 GetSize() {
            return size_;
        }
        void SetPosition(Math::Vector2 position) {
            position_ = position;
        }
        bool IsVisible() const {
            return isVisible_;
        }
        void SetVisible(bool flag) {
            isVisible_ = flag;
        }

        void Open() {
            isVisible_ = true;
        }

        void Close() {
            isVisible_ = false;
        }

    private:
        Math::Vector2 size_;
        Math::Vector2 position_;
        bool isVisible_{ true };
        std::string name_;
        int value_{ -1 };
    };
}

