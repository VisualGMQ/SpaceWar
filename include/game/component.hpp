#pragma once

#include "tinyengine/tinyengine.hpp"
#include "game/constants.hpp"
#include "game/global.hpp"

class MoveCmpt: public Component {
public:
    void Init(const Point& p) { position = p; oldPosition = position; }
    void Release() {}

    Point position;
    Point oldPosition;
};

class MotionCmpt: public Component {
public:
    void Init(const Point& spd, float maxSpd) {
        speed = spd;
        maxSpeed = maxSpd;
        acceleration = {0, 0};
    }
    void Release() {}

    Point speed;
    Point acceleration;

    float maxSpeed;
};

class CollisionCmpt: public Component {
public:
    void Init(const Size& size) { rect.w = size.w; rect.h = size.h; }
    void Release() {}

    Rect rect;
};

class BulletCmpt: public Component {
public:
    enum Type {
        Bullet = 1,
        Missile,
    };

    inline void Init(Type type, int damage, Entity* owner, Entity* target = nullptr) {
        this->owner = owner;
        this->damage = damage;
        this->target = target;
        this->type = type;
        rotation = 0;
        alive = true;
        liveTime = 0;
    }
    inline void Release() override {}

    Type type;
    int damage;
    Entity* owner;
    Entity* target;
    float rotation;
    bool alive;
    float liveTime;
};



class SpaceshipWeaponCmpt: public Component {
public:
    enum Type {
        Orientation = 0x01,
        FreeRotation = 0x02,
    };

    static constexpr int InfBullet = -1;

    void Init(const std::string& name,
              Type type,
              BulletCmpt::Type bulletType,
              Entity* owner,
              int damage,
              float shootSpeed,
              float maxSpeed,
              float duration,
              int bulletAmount = InfBullet) {
        this->name = name;
        this->type = type;
        this->bulletType = bulletType;
        this->owner = owner;
        this->damage = damage;
        this->shootSpeed = shootSpeed;
        this->shootDuration = duration;
        this->coolDown = 0;
        this->maxSpeed = maxSpeed;
        this->bulletAmount = bulletAmount;
    }

    void Release() {}
    bool IsCoolDowning() const { return coolDown >= 0; }
    Entity* ShootBullet(const Point& dir);
    Entity* ShootMissile(const Point& dir, Entity* target);

    Type type;
    BulletCmpt::Type bulletType;
    std::string name;
    int damage;
    float shootSpeed;
    float shootDuration;
    float coolDown;
    float maxSpeed;
    Entity* owner;
    int bulletAmount;
};

class SpaceshipArmorCmpt: public Component {
public:
    void Init(int defence, float duration) {
        this->defence = defence;
        this->recoverDuration = duration;
    }

    int defence;
    float recoverDuration;
};

class FreightShipCmpt: public Component {
public:
    void Init(SpaceshipWeaponCmpt* weapon) {
        this->weapon = weapon;
    }
    void Release() { ECSContext.DestroyComponent(weapon); }

    SpaceshipWeaponCmpt* weapon;
};


class FightShipCmpt: public Component {
public:
    void Init(SpaceshipWeaponCmpt* weapon1, SpaceshipWeaponCmpt* weapon2) {
        this->degree = 0;
        this->weapon1 = weapon1;
        this->weapon2 = weapon2;
    }
    void Release() {
        ECSContext.DestroyComponent(weapon1);
        ECSContext.DestroyComponent(weapon2);
    }

    float degree;
    SpaceshipWeaponCmpt* weapon1;
    SpaceshipWeaponCmpt* weapon2;
};

class LifeCmpt: public Component {
public:
    void Init(int hp) { this->hp = hp; }
    void Release() {}

    int hp;
};

class RenderCmpt: public Component {
public:
    enum Type {
        TypeTexture = 1,
        TypeTile,
    };

    void Init(Texture* image) {
        texture = image;
        type = TypeTexture;
    }
    void Init(const Tile& tile) {
        this->tile = tile;
        type = TypeTile;
    }
    void Release() {}

    Type type;
    union {
        Texture* texture;
        Tile tile;
    };
};

class PlanetCmpt: public Component {
public:
    void Init(const Point& position, const Size& size) {
        positionInSpace = position;
        generateMap(size);
    }

    Point positionInSpace;
    Unique<Mat<Entity*>> map;

private:
    void generateMap(const Size& size);
};

class EnergyProductCmpt: public Component {
public:
    void Init(int amount, float duration) {
        this->productAmount = amount;
        this->duration = duration;
        this->cooldown = duration;
        this->amount = 0;
    }
    bool IsCoolDowning() { return cooldown > 0; }
    void Release() {}

    float duration;
    float cooldown;
    int productAmount;
    int amount;
};

class GroupCmpt: public Component {
public:
    void Init(int group) {
        groupIdx = group;
    }
    void Release() {}

    int groupIdx;
};

class AICmpt: public Component {
public:
    using AIFunc = std::function<void(Entity*)>;

    void Init(AIFunc func) {
        this->func = func;
        target = nullptr;
    }
    void Release() {}

    AIFunc func;
    Entity* target;
};
