#include "game/ai.hpp"

Entity* findRandomEntity(Entity* self) {
    int groupIdx = Random<int>(0, 3);
    if (groupIdx == self->Get<GroupCmpt>()->groupIdx) {
        groupIdx ++;
        if (groupIdx >= 4) {
            groupIdx = 0;
        }
    }
    auto& group = Groups[groupIdx];
    if (group.Empty())
        return nullptr;
    return group.Get(Random<int>(1, group.Size()) - 1);
}

void FreightShipAI(Entity* self) {
    auto ai = self->Use<AICmpt>();
    if (!ai->target || !ai->target->IsAlive()) {
        ai->target = findRandomEntity(self);
    }
    if (!ai->target) return;

    auto pmove = ai->target->Get<MoveCmpt>();
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
    auto ai = self->Use<AICmpt>();
    if (!ai->target || !ai->target->IsAlive()) {
        ai->target = findRandomEntity(self);
    }
    if (!ai->target) return;

    auto pmove = ai->target->Get<MoveCmpt>();
    auto smove = self->Get<MoveCmpt>();
    auto dir = pmove->position - smove->position;

    auto motion = self->Use<MotionCmpt>();
    auto ship = self->Use<FightShipCmpt>();

    auto ndir = Normalize(dir);

    SpeedUp(*motion, *ship);

    auto shipDir = Rotate(Point{0, -1}, self->Get<FightShipCmpt>()->degree);
    auto cross = Cross(shipDir, ndir);
    if (cross > 0) {
        TurnRight(*self->Use<MotionCmpt>(), *ship);
    } else {
        TurnLeft(*self->Use<MotionCmpt>(), *ship);
    }
    if (abs(Cross(Normalize(motion->speed), Normalize(dir))) < std::sin(Radians(10))) {
        if (ship->weapon2->bulletAmount > 0 && Random(1.0f, 100.0f) < 5) {
            Shoot(*ship->weapon2, shipDir, ai->target);
        } else {
            Shoot(*ship->weapon1, shipDir);
        }
    }
}
