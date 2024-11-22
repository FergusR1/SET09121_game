//ghost.cpp
#include "ghost.h"
#include <cstdlib>
#include <ctime>
using namespace sf;
using namespace std;

float moveTimer = 0.f;
//Vector2i vecDir = {0,0};

void Ghost::Update(double dt) {
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

    Entity::Update(dt);
}

Ghost::Ghost() : _speed(200.0f), Entity(make_unique<CircleShape>(25.f)) {
    _vecDir = { 0,0 };
    _shape->setFillColor(Color::Cyan);
    _shape->setOrigin(Vector2f(25.f, 25.f));
}

//void Ghost::Render(sf::RenderWindow& window) const {
void Ghost::Render() const {
    Renderer::queue(_shape.get());
}

