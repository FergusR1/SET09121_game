//player.cpp
#include "player.h"
#include "../lib_tile_level_loader/LevelSystem.h"
using namespace sf;
using namespace std;

const Keyboard::Key controls[5] = {
    Keyboard::Right,   // Player Right
    Keyboard::Left,    // Player Left
    Keyboard::Up,      // Player Up
    Keyboard::Down,    // Player Down
    Keyboard::Space //fire bullet
};

bool validmove(Vector2f pos) {
    return (ls::getTileAt(pos) != ls::WALL);
}

void Player::Update(double dt) {
    //Move in four directions based on keys
    Vector2i dir = { 0,0 };
    dir.x = (Keyboard::isKeyPressed(controls[0]) ? 1 : 0) - (Keyboard::isKeyPressed(controls[1]) ? 1 : 0);
    dir.y = (Keyboard::isKeyPressed(controls[2]) ? 0 : 1) - (Keyboard::isKeyPressed(controls[3]) ? 0 : 1);

    Vector2<float> moveDir = { _speed * dir.x * (float)dt, _speed * dir.y * (float)dt };

    if (validmove(moveDir + getPosition())) {
        move(moveDir);
    }
    

    Entity::Update(dt);
}

Player::Player() : _speed(200.0f), Entity(make_unique<CircleShape>(25.f)) {
    _shape->setFillColor(Color::Magenta);
    _shape->setOrigin(Vector2f(25.f, 25.f));
}

void Player::Render(sf::RenderWindow& window) const {
    window.draw(*_shape);
}

