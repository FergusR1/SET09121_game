#include <SFML/Graphics.hpp>
#include <iostream>
#include "ship.h"

using namespace sf;
using namespace std;

const int gameWidth = 800;
const int gameHeight = 600;

Texture spritesheet;
Sprite invader;

CircleShape ball;
float ballRadius = 100.f;

vector<Ship*> ships;

void Load() {
	ball.setRadius(ballRadius);
	ball.setOrigin(ballRadius/2.f, ballRadius/2.f);
    ball.setPosition(Vector2f(gameWidth / 2.f, gameHeight / 2.f));
    ball.setFillColor(Color::Green);

    if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
        cerr << "Failed to load spritesheet!" << endl;
    }
    invader.setTexture(spritesheet);
    invader.setTextureRect(IntRect(Vector2i(0, 0), Vector2i(32, 32)));

    Invader* inv = new Invader(IntRect(Vector2i(0, 0), Vector2i(32, 32)), { 100,100 });
    ships.push_back(inv);
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

   
}

void Render(RenderWindow& window) {
    // Draw Everything
    window.draw(ball);
    window.draw(invader);
}

int main() {
    RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");
    Load();
    while (window.isOpen()) {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }
    return 0;
}