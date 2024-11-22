//"cmp_actor_movement.cpp"
#include "cmp_actor_movement.h"
#include "../lib_tile_level_loader/LevelSystem.h"

using namespace sf;

void ActorMovementComponent::update(double dt) {}

ActorMovementComponent::ActorMovementComponent(Entity* p)
    : _speed(100.0f), Component(p) {}

//bool ActorMovementComponent::validMove(const sf::Vector2f& pos) {
//    return (LevelSystem::getTileAt(pos) != LevelSystem::WALL);
//}

void ActorMovementComponent::move(const sf::Vector2f& p) {
    auto pp = _parent->getPosition() + p;
    _parent->setPosition(pp);
    //if (validMove(pp)) {
    //    ...
    //}
}

void ActorMovementComponent::move(float x, float y) {
    move(Vector2f(x, y));
}
float ActorMovementComponent::getSpeed() const { return _speed; }
void ActorMovementComponent::setSpeed(float speed) { _speed = speed; }


PlayerMovementComponent::PlayerMovementComponent(Entity* p)
    : ActorMovementComponent(p) {}

const Keyboard::Key controls[5] = {
    Keyboard::Right,   // Player Right
    Keyboard::Left,    // Player Left
    Keyboard::Up,      // Player Up
    Keyboard::Down,    // Player Down
    Keyboard::Space    // unused
};

void PlayerMovementComponent::update(double dt) {
    Vector2i dir = { 0,0 };
    dir.x = (Keyboard::isKeyPressed(controls[0]) ? 1 : 0) - (Keyboard::isKeyPressed(controls[1]) ? 1 : 0);
    dir.y = (Keyboard::isKeyPressed(controls[2]) ? 0 : 1) - (Keyboard::isKeyPressed(controls[3]) ? 0 : 1);

    Vector2<float> moveDir = { _speed * dir.x * (float)dt, _speed * dir.y * (float)dt };

    move(moveDir);
}


EnemyAIComponent::EnemyAIComponent(Entity* p)
    : ActorMovementComponent(p) {
    _vecDir = { 0,0 };
}

float moveTimer = 0.f;

void EnemyAIComponent::update(double dt) {
    srand(time(nullptr));
    //Move in four directions based on randomness
    if (moveTimer <= 0) {
        _vecDir = { 0,0 };
        moveTimer = 1.f;
        int dir = rand() % 4;
        switch (dir) {
        case 0:
            _vecDir.x = 1; //Move right
            break;
        case 1:
            _vecDir.x = -1; // Move left
            break;
        case 2:
            _vecDir.y = 1; // Move down
            break;
        case 3:
            _vecDir.y = -1; // Move up
            break;
        }
    }
    else {
        moveTimer -= dt;
    }

    Vector2<float> moveDir = { _speed * _vecDir.x * (float)dt, _speed * _vecDir.y * (float)dt };

    move(moveDir);
}
