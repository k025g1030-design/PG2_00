#pragma once
#include <Novice.h>
#include "Math.hpp"


namespace Component {
    class ImageSpan {
    public:
        explicit ImageSpan(Math::Vector2 size, Math::Vector2 position, int value) : size_(size), position_(position), value_(value){}
        explicit ImageSpan() {}

        void Render() const {
            if (!isVisible_) return;
            int x = static_cast<int>(position_.x);
            int y = static_cast<int>(position_.y);
            int w = static_cast<int>(size_.x);
            int h = static_cast<int>(size_.y);

            Novice::DrawBox(x, y, w, h, 0, 0x404040FF, kFillModeSolid);
            Novice::DrawBox(x, y, w, h, 0, 0xFFFFFFFF, kFillModeWireFrame);

            if (value_ != -1) {
                Novice::DrawSprite(x, y , value_, 1.0f, 1.0f, 0.0f, WHITE);
            }
            
        }

        void SetSize(Math::Vector2 size) {
            size_ = size;
        }
        Math::Vector2 GetSize() const {
            return size_;
        }

        void Open() {
            isVisible_ = true;
        }

        void Close() {
            isVisible_ = false;
        }

        void SetPosition(Math::Vector2 position) {
            position_ = position;
        }
        Math::Vector2 GetPosition() const {
            return position_;
        }
        bool IsVisible() const {
            return isVisible_;
        }
        void SetVisible(bool flag) {
            isVisible_ = flag;
        }

    private:
        Math::Vector2 size_;
        Math::Vector2 position_;
        bool isVisible_{ true };
        int value_{ -1 };
    };
}

