//"cmp_actor_movement.h"
#pragma once
#include <ecm.h>
#include "../lib_tile_level_loader/LevelSystem.h"

class ActorMovementComponent : public Component {
protected:
    bool validMove(const sf::Vector2f&);
    float _speed;

public:
    explicit ActorMovementComponent(Entity* p);
    ActorMovementComponent() = delete;

    float getSpeed() const;
    void setSpeed(float _speed);

    void move(const sf::Vector2f&);
    void move(float x, float y);

    void render() override {}
    void update(double dt) override;
};

class PlayerMovementComponent : public ActorMovementComponent {
public:
    PlayerMovementComponent::PlayerMovementComponent(Entity* p);
    PlayerMovementComponent() = delete;
    void update(double dt) override;
};

class EnemyAIComponent : public ActorMovementComponent {
protected:
    sf::Vector2f _direction;
    enum state { ROAMING, ROTATING, ROTATED };
    state _state = ROTATING;
public:
    EnemyAIComponent::EnemyAIComponent(Entity* p);
    EnemyAIComponent() = delete;
    void update(double dt) override;
};