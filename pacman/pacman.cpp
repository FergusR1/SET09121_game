//pacman.cpp
#include "pacman.h"
#include "player.h"
#include "ghost.h"
#include <iostream>

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
	auto player = std::make_unique<Player>();
	_ents.list.push_back(std::move(player));

	for (int i = 0; i < 4; i++) {
		auto ghost = std::make_unique<Ghost>();
		ghost->setPosition({ 400.f,400.f });
		_ents.list.push_back(std::move(ghost));
	}
}
