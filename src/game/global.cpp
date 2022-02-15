#include "game/global.hpp"
#include "game/component.hpp"

Context ECSContext;
SystemManager SystemMgr;
Unique<TileSheet> GameTileSheet;
std::unordered_map<std::string, Unique<Sound>> Sounds;

QuickList<Entity*> Bullets;
QuickList<Entity*> Entities;

Entity* PlayerSpaceship = nullptr;
GameInitInfo InitInfo;

std::array<QuickList<Entity*>, 4> Groups;

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

Point MapGlobal2PlayerCoord(const Point& pos) {
    if (PlayerSpaceship && PlayerSpaceship->Has<MoveCmpt>()) {
        return pos - PlayerSpaceship->Get<MoveCmpt>()->position + GameWindowSize / 2;
    } else {
        return pos;
    }
}

Point MapPlayerCoord2Global(const Point& pos) {
    if (PlayerSpaceship && PlayerSpaceship->Has<MoveCmpt>()) {
        return pos + PlayerSpaceship->Get<MoveCmpt>()->position - GameWindowSize / 2;
    } else {
        return pos;
    }
}
