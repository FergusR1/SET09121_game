#include <SFML/Graphics.hpp>
#include <iostream>
#include "ship.h"
#include "bullet.h"

using namespace sf;
using namespace std;

const int gameWidth = 800;
const int gameHeight = 600;

Texture spritesheet;
Sprite invader;

CircleShape ball;
float ballRadius = 100.f;

vector<Ship*> ships;
Ship* player = nullptr;

//int rowSize = 44;
//bool offset = true;

void Load() {

    if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
        cerr << "Failed to load spritesheet!" << endl;
    }
    invader.setTexture(spritesheet);
    invader.setTextureRect(IntRect(Vector2i(0, 0), Vector2i(32, 32)));

    Invader::speed = 40.f;
    Player::speed = 50.f;

    int invaders_rows = 5;
    int invaders_columns = 12;

    IntRect rect = IntRect(Vector2i(0, 0), Vector2i(32, 32));
    
    player = new Player();
    ships.push_back(player);

    for (int r = 0; r < invaders_rows; ++r) {
        //auto rect = IntRect(Vector2i(0, 0), Vector2i(32, 32));
        for (int c = 0; c < invaders_columns; ++c) {
            Vector2f position = Vector2f(c*32+16,r*32+16);
            auto inv = new Invader(rect, position);
            ships.push_back(inv);
        }
    }

    Bullet::Init();

    //for (int i = 0; i < 968; i++) {
    //    float horizontalPOS = (16 + (16 * (((i / rowSize)) % 2)) + (32 * (i % rowSize)));
    //    float verticalPOS = (16 + (32 * (i / (rowSize))));
    //    Invader* inv = new Invader(IntRect(Vector2i(0, 0), Vector2i(32, 32)), Vector2f(horizontalPOS,verticalPOS));
    //    ships.push_back(inv);
    //}
    
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

    //call invaders update function
    for (auto& s : ships) {
        s->Update(dt);
    };

    //call invaders render function
    for (const auto s : ships) {
        window.draw(*s);
    }

    //call bullets render & update function
    Bullet::Render(window);
    Bullet::Update(dt);
    
}
/*
void Render(RenderWindow& window) {
    // Draw Everything
    //window.draw(ball);
    //window.draw(invader);
}*/

int main() {
    RenderWindow window(VideoMode(gameWidth, gameHeight), "Space Invaders");
    Load();
    
    while (window.isOpen()) {
        window.clear();
        Update(window);
        //Render(window);
        window.display();
    }
    return 0;
}