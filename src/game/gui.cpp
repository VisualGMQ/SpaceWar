#include "game/gui.hpp"
#include "tinyengine/event.hpp"

bool Button(Texture* texture, const Point& pos, const Size& size) {
    Renderer::DrawTexture(texture, nullptr, pos, size);
    if (IsLeftPressing() &&
        IsPointInRect(GetMousePosition(), Rect{pos.x - size.w / 2, pos.y - size.h / 2, size.w, size.h})) {
        return true;
    } else {
        return false;
    }
}
