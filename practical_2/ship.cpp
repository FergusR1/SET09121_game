//ship.cpp
#include "ship.h"
#include "game.h"
#include "bullet.h"
#include <iostream>

using namespace sf;
using namespace std;

Ship::Ship() {};

Ship::Ship(IntRect ir) : Sprite() {
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
};

void Ship::Update(const float& dt) {}

//Define the ship deconstructor. 
//Although we set this to pure virtual, we still have to define it.
Ship::~Ship() = default;




Invader::Invader() : Ship() {}

bool Invader::direction;
float Invader::speed;
static float invaderFiretime = 0.0f;

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
	setOrigin(Vector2f(16.f, 16.f));
	setPosition(pos);
}

void Invader::Update(const float& dt) {
    
    Ship::Update(dt);
    invaderFiretime -= dt;

    move(Vector2f(dt * (direction ? 1.0f : -1.0f) * speed, 0.0f));

    if ((direction && getPosition().x > gameWidth - 16) ||
        (!direction && getPosition().x < 16)) {
        direction = !direction;
        for (int i = 0; i < ships.size(); ++i) {
            ships[i]->move(Vector2f(0.0f, 24.0f));
        }
    }

    if (invaderFiretime <= 0 && rand() % 100 == 0) {
        Bullet::Fire(getPosition(), true);
        invaderFiretime = 4.0f + (rand() % 60);
    }


    if (_exploded) {
        explodeTimer -= dt;
        if (explodeTimer <= 0) {
            setPosition({-100, 0});
        }
    }
}

void Invader::move(Vector2f dir) {
    setPosition(getPosition()+dir);
}

const Keyboard::Key controls[3] = {
    Keyboard::Right,   // Player1 Right
    Keyboard::Left,   // Player1 Left
    Keyboard::Space //fire bullet
};

float Player::speed;

Player::Player() : Ship(IntRect(Vector2i(160, 32), Vector2i(32, 32))) {
    setPosition({ gameWidth * .5f, gameHeight - 32.f });
}

static float playerFiretime = 0.0f;

void Player::Update(const float& dt) {
    
    Ship::Update(dt);
    playerFiretime -= dt;

    int dir = (Keyboard::isKeyPressed(controls[0]) ? 1 : 0) -
        (Keyboard::isKeyPressed(controls[1]) ? 1 : 0);

    Vector2f currentPOS = getPosition();
    Vector2f movePOS = Vector2f(currentPOS.x + speed * dir * dt, currentPOS.y);
    if (movePOS.x < gameWidth - 8 || movePOS.x > 8) {
        setPosition(movePOS);
    }
    
    if (Keyboard::isKeyPressed(controls[2]) && playerFiretime <= 0) {
        Bullet::Fire(getPosition(), false);
        //cout << "FIRING - ";
        playerFiretime = .7f;

    }


}

void Player::move(Vector2f dir) {
    //setPosition(this->getPosition() + dir);
}

void Ship::Explode() {
    setTextureRect(IntRect(Vector2i(128, 32), Vector2i(32, 32)));
    _exploded = true;
    explodeTimer = 0.5f;
}

bool Ship::is_exploded() const {
    return _exploded;
}