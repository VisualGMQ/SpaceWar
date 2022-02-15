#pragma once

enum PlaneType {
    FreightShip = 1,
    FightShip,
};

struct GameInitInfo {
    int planeType;
    int groupNum;
    int planeNum;
};
