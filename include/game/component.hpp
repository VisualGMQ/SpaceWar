#pragma once

#include "tinyengine/tinyengine.hpp"
#include "game/constants.hpp"

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

class FightShipCmpt: public Component {
public:
    void Init(float degree) {
        this->degree = degree;
    }
    void Release() {}

    float degree;
};

class FreightShipCmpt: public Component {
public:
    void Init() {}
    void Release() {}
};

class SpaceshipWeaponCmpt: public Component {
public:
    enum Type {
        Orientation = 0x01,
        FreeRotation = 0x02,
    };

    void Init(Type type,
              Entity* owner,
              int damage,
              float shootSpeed,
              float maxSpeed,
              float duration) {
        this->type = type;
        this->owner = owner;
        this->damage = damage;
        this->shootSpeed = shootSpeed;
        this->shootDuration = duration;
        this->maxSpeed = maxSpeed;
    }

    void Release() {}
    bool IsCoolDowning() const { return coolDown >= 0; }
    Entity* ShootBullet(const Point& dir);

    Type type;
    int damage;
    float shootSpeed;
    float shootDuration;
    float coolDown;
    float maxSpeed;
    Entity* owner;
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

class BulletCmpt: public Component {
public:
    inline void Init(int damage, Entity* owner) {
        this->owner = owner;
        this->damage = damage;
        alive = true;
    }
    inline void Release() override {}

    int damage;
    Entity* owner;
    bool alive;
};
