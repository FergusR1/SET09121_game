#include <SFML/Graphics.hpp>
#include <iostream>
#include <../lib_ecm/ecm.h>
#include "system_renderer.h"
#include "pacman.h"

using namespace sf;
using namespace std;

const int gameWidth = 1920;
const int gameHeight = 1080;

//unique_ptr<Player> player = nullptr;
//vector<unique_ptr<Ghost>> ghosts = {};
//EntityManager em;

void Load() {
    
    //cout << "main.load.start\n";
    // Load Scene-Local Assets
    gameScene.reset(new GameScene());
    menuScene.reset(new MenuScene());
    gameScene->load();
    menuScene->load();
    // Start at main menu
    activeScene = menuScene;
    //cout << "main.load.end\n";
}

//void Update(RenderWindow& window) {

void Update() {
    //cout << "main.update.start\n";
    // Reset clock, recalculate deltatime
    static Clock clock;
    double dt = clock.restart().asSeconds();
    activeScene->update(dt);
    
    //cout << "main.update.end\n";
    //em.update(dt);
    //Renderer::queue(e.get()->getShape());

    //Renderer::queue(player.get()->getShape());
}

//void Render(sf::RenderWindow& window) {
 void Render() {
    //em.render(window);
    //em.render();
     //cout << "main.render.start\n";

    activeScene->render();
    Renderer::render();

    //cout << "main.render.end\n";
}

int main() {

    
    RenderWindow window(VideoMode(gameWidth, gameHeight), "PacMan");
    Renderer::initialise(window);
    Load();

    while (window.isOpen()) {

        // check and consume events
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
                break;
            }
        }

        // Quit Via ESC Key
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }

        window.clear();
        //Update(window);
        Update();
        //Render(window);
        Render();
        window.display();
    }
    return 0;

}