#include "game/global.hpp"

Context ECSContext;
SystemManager SystemMgr;
Unique<TileSheet> GameTileSheet;
std::unordered_map<std::string, Unique<Sound>> Sounds;
QuickList<Entity*> Bullets;
QuickList<Entity*> Entities;

void loadImages() {
    GameTileSheet.reset(new TileSheet("assets/tilesheet.png", 8, 8));
}

void loadSounds() {
    Sounds["shoot"] = std::make_unique<Sound>("assets/shoot.wav");
}

void LoadResources() {
    loadImages();
    loadSounds();
}
