#include "game/gui.hpp"
#include "tinyengine/event.hpp"

bool Button(Texture* texture, const Point& pos, const Size& size, bool hflip) {
    Renderer::DrawTexture(texture, nullptr, pos, size, 0, hflip ? Renderer::FlipFlag::Horizontal : Renderer::FlipFlag::NoFlip); 
    Rect rect = Rect{pos.x - size.w / 2, pos.y - size.h / 2, size.w, size.h};
    if (IsPointInRect(GetMousePositionMapped(), rect)) {
        Renderer::SetDrawColor(Color{1, 1, 1, 0.2});
        Renderer::FillRect(rect);
        return IsLeftPressed();
    } else {
        return false;
    }
}
