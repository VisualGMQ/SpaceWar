#pragma once

#include "texture.hpp"

struct Tile {
    Texture* texture;
    Rect rect;
    Size size;
};

class TileSheet final {
public:
    TileSheet(const std::string& filename, int x, int y);

    const Tile GetTile(int x, int y);
    Texture* GetTexture() { return texture_.get(); }

private:
    Unique<Texture> texture_;
    Size size_;
};
