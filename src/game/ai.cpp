#include "game/ai.hpp"

void FreightShipAI(Entity* self) {
    auto pmove = PlayerSpaceship->Get<MoveCmpt>();
    auto smove = self->Get<MoveCmpt>();
    auto dir = pmove->position - smove->position;
    if (Len2(dir) > 250000) {
        auto motion = self->Use<MotionCmpt>();
        if (dir.x < 0) {
            MoveLeft(*motion);
        } else {
            MoveRight(*motion);
        }
        if (dir.y < 0) {
            MoveUp(*motion);
        } else {
            MoveDown(*motion);
        }
    } else {
        Shoot(*self->Get<FreightShipCmpt>()->weapon, dir);
    }
}

void FightShipAI(Entity* self) {
    auto pmove = PlayerSpaceship->Get<MoveCmpt>();
    auto smove = self->Get<MoveCmpt>();
    auto dir = pmove->position - smove->position;

    auto motion = self->Use<MotionCmpt>();
    auto ship = self->Use<FightShipCmpt>();

    auto nspd = Normalize(motion->speed),
         ndir = Normalize(dir);

    SpeedUp(*motion, *ship);

    auto cross = Cross(nspd, ndir);
    if (cross > std::sin(Radians(80))) {
        TurnLeft(*ship);
    } else if (cross < std::sin(Radians(10))) {
        TurnRight(*ship);
    }
    // if (Cross(Normalize(motion->speed), Normalize(dir)) < std::sin(Radians(10))) {
    //     if (ship->weapon2->bulletAmount > 0 && Random(1.0f, 100.0f) < 5) {
    //         Shoot(*ship->weapon2, dir, PlayerSpaceship);
    //     } else {
    //         Shoot(*ship->weapon1, dir);
    //     }
    // }
}
