#include "ecm.h"
#include <SFML/Graphics.hpp>
using namespace std;



Entity::Entity() : 
	_alive (true), 
	_fordeletion(false), 
	_rotation(0.f), 
	_visible(true) {}

void Entity::update(double dt) {
	setPosition(_position);

	if (_alive) {
		for (auto c : _components) {
			c->update(dt);
		}
	}
}

void Entity::render() {
	if (_visible) {
		for (auto c : _components) {
			c->render();
		}
	}
	
}

const sf::Vector2f& Entity::getPosition() const {
	return _position;
}

inline void Entity::setPosition(const sf::Vector2f& pos) { 
	_position = pos; 
}

bool Entity::is_fordeletion() const {
	return _fordeletion;
}

float Entity::getRotation() const {
	return _rotation;
}

void Entity::setRotation(float rot) {
	_rotation = rot;
}

bool Entity::isAlive() const {
	return _alive;
}

void Entity::setAlive(bool alive) {
	_alive = alive;
}

void Entity::setForDelete() {
	_fordeletion = true;
}

bool Entity::isVisible() const {
	return _visible;
}

void Entity::setVisible(bool vis) {
	_visible = vis;
}






Component::Component(Entity* const p) : 
	_parent(p), 
	_fordeletion(false) {}

bool Component::is_fordeletion() const {
	return _fordeletion;
}

//Component::~Component() { cout << "~component"; }

void EntityManager::update(double dt) {
	for (auto entity : list) {
		entity.get()->update(dt);
	}
}

void EntityManager::render() {
	for (auto entity : list) {
		entity.get()->render();
	}
}
