//pacman.cpp
#include "pacman.h"
#include "../lib_ecm/ecm.h"
#include <iostream>
#include "cmp_sprite.h"

#define GHOSTS_COUNT 4

std::shared_ptr<Scene> gameScene = std::make_shared<GameScene>();
std::shared_ptr<Scene> menuScene = std::make_shared<MenuScene>();
std::shared_ptr<Scene> activeScene;




void MenuScene::update(double dt) {
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		activeScene = gameScene;
	}
	Scene::update(dt);
	text.setString("Almost Pacman");
}

void MenuScene::render() {
	if (text.getFont() != nullptr) {
		Renderer::queue(&text);
	}
	else {
		std::cerr << "Text has no font set!" << std::endl;
	}
	Scene::render();
}


void MenuScene::load() {
	//Set up the text element here!
	static sf::Font font; 
	if (!font.loadFromFile("res/fonts/RobotoMono-Regular.ttf")) { 
		std::cerr << "Failed to load font!" << std::endl; 
	}
	// Set text element to use font
	text.setFont(font);
	// set the character size to 24 pixels
	text.setCharacterSize(24);
	text.setPosition({100.f, 100.f});
}

void GameScene::respawn()
{
}

void GameScene::update(double dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
		activeScene = menuScene;
	}
	Scene::update(dt);
}

void GameScene::render() {
	Scene::render();
}

void GameScene::load() {

	{
		auto pl = std::make_shared<Entity>();

		auto s = pl->addComponent<ShapeComponent>();
		s->setShape<sf::CircleShape>(12.f);
		s->getShape().setFillColor(sf::Color::Yellow);
		s->getShape().setOrigin(sf::Vector2f(12.f, 12.f));
		pl->setVisible(true);
		

		_ents.list.push_back(pl);
	}

	const sf::Color ghost_cols[]{ {208, 62, 25},    // red Blinky
								 {219, 133, 28},   // orange Clyde
								 {70, 191, 238},   // cyan Inky
								 {234, 130, 229} }; // pink Pinky

	for (int i = 0; i < GHOSTS_COUNT; ++i) {
		auto ghost = std::make_shared<Entity>();
		auto s = ghost->addComponent<ShapeComponent>();
		s->setShape<sf::CircleShape>(12.f);
		s->getShape().setFillColor(ghost_cols[i % 4]);
		s->getShape().setOrigin(sf::Vector2f(12.f, 12.f));

		_ents.list.push_back(ghost);
	}
}
