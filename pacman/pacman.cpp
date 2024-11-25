//pacman.cpp
#include "pacman.h"
#include "../lib_ecm/ecm.h"
#include <iostream>
#include "cmp_sprite.h"
#include "cmp_actor_movement.h"
#include "../lib_tile_level_loader/LevelSystem.h"
#include "cmp_pickup.h"
//#include "../lib_tile_level_loader/LevelSystem.cpp"

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

std::vector<std::shared_ptr<Entity>> nibbles = {};

void GameScene::respawn() {
	player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	player->getCompatibleComponent<ActorMovementComponent>()[0]->setSpeed(150.f);

	auto ghost_spawns = ls::findTiles(ls::ENEMY);
	for (auto& g : ghosts) {
		g->setPosition(
			ls::getTilePosition(ghost_spawns[rand() % ghost_spawns.size()]));
		g->getCompatibleComponent<ActorMovementComponent>()[0]->setSpeed(100.0f);
		g->setAlive(true);
	}

	std::cout << "PRE NIBBLES" << std::endl;
	//clear any remaining nibbles
	for (auto n : nibbles) {
		n->setForDelete();
		n.reset();
	}
	nibbles.clear();

	//white nibbles
	auto nibbleLoc = LevelSystem::findTiles(LevelSystem::EMPTY);
	for (const auto& nl : nibbleLoc) {
		auto cherry = makeNibble(nl, false);
		//add to _ents and nibbles list
		_ents.list.push_back(cherry);
	}
	//blue nibbles
	nibbleLoc = LevelSystem::findTiles(LevelSystem::WAYPOINT);
	for (const auto& nl : nibbleLoc) {
		auto cherry = makeNibble(nl, true);
		//add to _ents and nibbles list
		_ents.list.push_back(cherry);
		nibbles.push_back(cherry);
	}
	std::cout << "POST NIBBLES" << std::endl;
}

void GameScene::update(double dt) {
	std::cout << "UPDATE START" << std::endl;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
		activeScene = menuScene;
	}
	//"pacman.cpp"
	std::cout << "GHOS SIZE = " << ghosts.size() << std::endl;
	for (auto& g : ghosts) {
		
		if (length(g->getPosition() - player->getPosition()) < 30.0f) {
			respawn();
		}
		std::cout << "GHOST FOR" << std::endl;
	}
	Scene::update(dt);
	std::cout << "UPDATE END" << std::endl;
}

void GameScene::render() {
	ls::Render(Renderer::getWindow());
	Scene::render();
}




std::shared_ptr<Entity> GameScene::makeNibble(const sf::Vector2ul& nl, bool big) {
	auto cherry = std::make_shared<Entity>();
	auto s = cherry->addComponent<ShapeComponent>();
	
	//set colour
	if (big) {
		s->setShape<sf::CircleShape>(6.f);
		s->getShape().setOrigin(sf::Vector2f(6.f, 6.f));
		s->getShape().setFillColor(sf::Color::Color(150, 170, 255, 255));
	}
	else {
		s->setShape<sf::CircleShape>(3.f);
		s->getShape().setOrigin(sf::Vector2f(3.f, 3.f));
		s->getShape().setFillColor(sf::Color::White);
	}

	cherry->addComponent<PickupComponent>(big);
	cherry->setPosition(ls::getTilePosition(nl) + sf::Vector2f(10.f, 10.f));
	return cherry;
}



void GameScene::load() {

	
	ls::loadLevelFile("res/levels/pacman.txt", 25.0f);
	player = std::make_shared<Entity>();

	auto s = player->addComponent<ShapeComponent>();
	s->setShape<sf::CircleShape>(12.f);
	s->getShape().setFillColor(sf::Color::Yellow);
	s->getShape().setOrigin(sf::Vector2f(12.f, 12.f));
	player->addComponent<PlayerMovementComponent>();
		
	_ents.list.push_back(player);

	

	const sf::Color ghost_cols[]{ {208, 62, 25},    // red Blinky
								 {219, 133, 28},   // orange Clyde
								 {70, 191, 238},   // cyan Inky
								 {234, 130, 229} }; // pink Pinky

	for (int i = 0; i < GHOSTS_COUNT; ++i) {
		auto ghost = std::make_shared<Entity>();
		ghost->setAlive(false);
		auto s = ghost->addComponent<ShapeComponent>();
		s->setShape<sf::CircleShape>(12.f);
		s->getShape().setFillColor(ghost_cols[i % 4]);
		s->getShape().setOrigin(sf::Vector2f(12.f, 12.f));
		ghost->addComponent<EnemyAIComponent>();
		ghost->setPosition({ 200.f, 200.f });

		ghosts.push_back(ghost);
		_ents.list.push_back(ghost);
	}

	respawn();
}


