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
    GameTileSheet.reset(new TileSheet("assets/tilesheet.png", 7, 1));
}

void loadSounds() {
    Sounds["shoot"] = std::make_unique<Sound>("assets/shoot.wav");
    Sounds["hurt"] = std::make_unique<Sound>("assets/hurt.wav");
    Sounds["explosion"] = std::make_unique<Sound>("assets/explose.wav");
    Sounds["missile"] = std::make_unique<Sound>("assets/missile.wav");
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
