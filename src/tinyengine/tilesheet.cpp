#include "tilesheet.hpp"

TileSheet::TileSheet(const std::string& filename, int x, int y) {
    texture_.reset(new Texture(filename));
    size_.x = x;
    size_.y = y;
}

const Tile TileSheet::GetTile(int x, int y) {
    Size size = texture_->GetSize() / size_;
    return {texture_.get(),
            Rect{size.w * x, size.h * y, size.w, size.h},
            size};
}
