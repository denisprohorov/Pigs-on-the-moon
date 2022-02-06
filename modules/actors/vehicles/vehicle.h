#pragma once

#include "map/hex.h"
#include "enums/action.h"
#include <map>
#include <vector>

class Vehicle {
public:
    Vehicle(int ownerId, int hp, int speed, int damage = 1)
            : PLAYER_ID(ownerId),
              DAMAGE(damage),
              health(hp),
              SPEED_POINTS(speed),
              DESTRUCTION_POINTS(hp) {}

    bool Move(Hex *newPos);

    std::multimap<int, Point> GetAvailableMovePoints(const Point &target);

    virtual bool IsAvailableForShoot(Vehicle *enemy) = 0;

    virtual Action PriorityAction() const = 0;

    virtual Point Shoot(Vehicle *enemy) { return enemy->GetCurrentPosition();};

    void IncCapture() { capturePoints++; }

    void DropCapture() { capturePoints = 0; }

    void Update(int health, Hex *newPos, int capture);

    [[nodiscard]] int GetPlayerId() const { return PLAYER_ID; }

    [[nodiscard]] const Point &GetSpawn() const { return spawnPosition->GetCoordinates(); }

    [[nodiscard]] const Point &GetCurrentPosition() const { return currentPosition->GetCoordinates(); }

    Hex *GetHexOfCurrentPosition() const { return currentPosition; }

    int GetHp() const { return health; }

    bool IsAlive() const { return health > 0; }

    void InitSpawn(Hex *p);

    void Respawn();

    int GetHit(int damage = 1);

private:
    const int PLAYER_ID;
    int health;
    const int DESTRUCTION_POINTS;
    const int SPEED_POINTS;
    const int DAMAGE;
    int capturePoints = 0;
    Hex *spawnPosition = nullptr;
    Hex *currentPosition = nullptr;

    bool IsEnemy(Vehicle *v) const { return this->PLAYER_ID != v->PLAYER_ID; }
};

