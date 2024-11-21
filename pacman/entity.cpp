//entity.cpp
#include "entity.h"
using namespace std;
using namespace sf;

const Vector2f Entity::getPosition() { return _position; }

void Entity::setPosition(const Vector2f& pos) { _position = pos; }

void Entity::move(const Vector2f& pos) { _position += pos; }

void Entity::Update(const double dt) {
    _shape->setPosition(_position);
}

Entity::Entity(unique_ptr<Shape> s) : _shape(std::move(s)) {}

sf::Shape* Entity::getShape() {
    return _shape.get();
}

void EntityManager::update(double dt) {
    for (auto entity : list) {
        entity.get()->Update(dt);
    }
}

//void EntityManager::render(sf::RenderWindow & window) {
void EntityManager::render() {
    for (auto entity : list) {
       // entity.get()->Render(window);
        entity.get()->Render();
    }
}
