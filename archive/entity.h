//entity.h

#pragma once

#include <SFML/Graphics.hpp>
#include <../pacman/system_renderer.h>
#include <memory>

class Entity {
protected:
	std::unique_ptr<sf::Shape> _shape;
	sf::Vector2f _position;
	Entity(std::unique_ptr<sf::Shape> shp);

public:
	Entity() = delete;
	virtual ~Entity() = default;

	virtual void Update(const double dt);
	//virtual void Render(sf::RenderWindow& window) const = 0;
	virtual void Render() const = 0;

	const sf::Vector2f getPosition();
	void setPosition(const sf::Vector2f& pos);
	void move(const sf::Vector2f& pos);
	sf::Shape* getShape();
};

struct EntityManager {
	std::vector<std::shared_ptr<Entity>> list;
	void update(double dt);
	//void render(sf::RenderWindow& window);
	void render();
};
