#include "game/global.hpp"

Context ECSContext;
SystemManager SystemMgr;
std::unordered_map<std::string, Unique<TileSheet>> TileSheets;
std::unordered_map<std::string, Unique<Sound>> Sounds;
std::string TileSheetName = "TileSheet";
QuickList<Entity*> Bullets;
EntityList Entities;

void loadImages() {
    TileSheets[TileSheetName] = std::make_unique<TileSheet>("assets/tilesheet.png", 8, 8);
}

void loadSounds() {
    Sounds["shoot"] = std::make_unique<Sound>("assets/shoot.wav");
}

void LoadResources() {
    loadImages();
    loadSounds();
}
