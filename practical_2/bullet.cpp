//bullet.cpp
#include "bullet.h"
#include "game.h"
#include <iostream>
using namespace sf;
using namespace std;

//static unsigned char bulletPointer;
//static Bullet bullets[256];

Bullet Bullet::bullets[256];
unsigned char Bullet::bulletPointer = 0;

//Set all the bullets to -100, -100, set the spritesheet, set origin
void Bullet::Init() {
    IntRect rect = IntRect(Vector2i(0, 0), Vector2i(32, 32));

    for (int i = 0; i < 256; i++) {
        Bullet::bullets[i].setOrigin(Vector2f(16.f, 16.f));
        Bullet::bullets[i].setTexture(spritesheet);  cout << "setTexture - ";
        Bullet::bullets[i].setTextureRect(rect);
        Bullet::bullets[i].setPosition({ -100.0f,-100.0f });
    }
}

void Bullet::Update(const float& dt) {
    for (auto& b : bullets) {
        b._Update(dt);
    }
}

void Bullet::Render(RenderWindow& window) {
    for (const auto b : bullets) {
        window.draw(b);
    }
}

//Chose an inactive bullet and use it.
void Bullet::Fire(const Vector2f& pos, const bool mode) {
    cout << "Fire - ";
    bullets[bulletPointer]._mode = mode;
    bullets[bulletPointer].setPosition({ pos.x + 16, pos.y - 16 });
    bulletPointer++;
}



void Bullet::_Update(const float& dt) {
    //.cout << "Fire - ";
    if (getPosition().y < -32 || getPosition().y > gameHeight + 32) {
        //off screen - do nothing
        return;
    }
    else {
        move(Vector2f(0, dt * 200.0f * (_mode ? 1.0f : -1.0f)));
        const FloatRect boundingBox = getGlobalBounds();

        for (auto s : ships) {
            if (!_mode && s == player) {
                //player bulelts don't collide with player
                continue;
            }
            if (_mode && s != player) {
                //invader bullets don't collide with other invaders
                continue;
            }
            if (!s->is_exploded() &&
                s->getGlobalBounds().intersects(boundingBox)) {
                //Explode the ship
                s->Explode();
                //warp bullet off-screen
                setPosition(Vector2f(-100, -100));
                return;
            }
        }
    }
}
Bullet::Bullet()
{
}
;