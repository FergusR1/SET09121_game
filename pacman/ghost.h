//ghost.h
#pragma once
#include "entity.h"

class Ghost : public Entity {
private:
	float _speed;
	sf::Vector2i _vecDir;

public:
	void Update(double dt) override;
	Ghost();
	//void Render(sf::RenderWindow& window) const override;
	void Render() const override;
};