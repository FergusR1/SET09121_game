#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"
#include "entity.h"
#include "LevelSystem.h"

using namespace sf;
using namespace std;

const int gameWidth = 1920;
const int gameHeight = 1080;

unique_ptr<Player> player = nullptr;

void Load() {
    player = make_unique<Player>();
    player->setPosition({100.f,100.f});

    ls::loadLevelFile("res/levels/level_1.txt", 50.f);

    // Print the level to the console
    for (size_t y = 0; y < ls::getHeight(); ++y) {
        for (size_t x = 0; x < ls::getWidth(); ++x) {
            cout << ls::getTile({ x, y });
        }
        cout << endl;
    }
}

void Update(RenderWindow& window) {

    // Reset clock, recalculate deltatime
    static Clock clock;
    float dt = clock.restart().asSeconds();

    // check and consume events
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
            return;
        }
    }

    // Quit Via ESC Key
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        window.close();
    }

    ls::Render(window);
    player->Update(dt);
    player->Render(window);
    

}

int main() {

    RenderWindow window(VideoMode(gameWidth, gameHeight), "TileEngine");
    Load();

    while (window.isOpen()) {
        window.clear();
        Update(window);
        window.display();
    }
    return 0;
}