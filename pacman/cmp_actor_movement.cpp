//"cmp_actor_movement.cpp"
#include "cmp_actor_movement.h"


#define ls LevelSystem

using namespace sf;

void ActorMovementComponent::update(double dt) {}

ActorMovementComponent::ActorMovementComponent(Entity* p) : _speed(100.0f), Component(p) {}

bool ActorMovementComponent::validMove(const sf::Vector2f& pos) {
    return (LevelSystem::getTileAt(pos) != LevelSystem::WALL);
}

void ActorMovementComponent::move(const sf::Vector2f& p) {
    auto pp = _parent->getPosition() + p;
    
    if (validMove(pp)) {
        _parent->setPosition(pp);
    }
}

void ActorMovementComponent::move(float x, float y) {
    move(Vector2f(x, y));
}
float ActorMovementComponent::getSpeed() const { return _speed; }
void ActorMovementComponent::setSpeed(float speed) { _speed = speed; }


PlayerMovementComponent::PlayerMovementComponent(Entity* p) : ActorMovementComponent(p) {}

const Keyboard::Key controls[5] = {
    Keyboard::Right,   // Player Right
    Keyboard::Left,    // Player Left
    Keyboard::Up,      // Player Up
    Keyboard::Down,    // Player Down
    Keyboard::Space    // unused
};

void PlayerMovementComponent::update(double dt) {
    Vector2i dir = { 0,0 };
    dir.x = (Keyboard::isKeyPressed(controls[0]) ? 1 : 0) - (Keyboard::isKeyPressed(controls[1]) ? 1 : 0);
    dir.y = (Keyboard::isKeyPressed(controls[2]) ? 0 : 1) - (Keyboard::isKeyPressed(controls[3]) ? 0 : 1);

    Vector2<float> moveDir = { _speed * dir.x * (float)dt, _speed * dir.y * (float)dt };

    move(moveDir);
}


static const Vector2i directions[] = { {1, 0}, {0, 1}, {0, -1}, {-1, 0} };

EnemyAIComponent::EnemyAIComponent(Entity* p)
    : ActorMovementComponent(p) {
}

void EnemyAIComponent::update(double dt) {

    //amount to move
    const auto mva = (float)(dt * _speed);
    //Curent position
    const Vector2f pos = _parent->getPosition();
    //Next position
    const Vector2f newpos = pos + _direction * mva;
    //Inverse of our current direction
    const Vector2i baddir = -1 * Vector2i(_direction);
    //Random new direction
    Vector2i newdir = directions[(rand() % 4)];

    float tileSize = ls::getTileSize();
    int tries = 10;

    switch (_state) {
    case ROAMING:
        //std::cout << "ROAMING START\n";
        if (ls::getTileAt(pos) == ls::WAYPOINT || ls::getTileAt(pos + _direction * tileSize ) == ls::WALL)// Wall in front or at waypoint
        {
            _state = ROTATING;
        }
        else {
            move(_direction * mva);
        }
        //std::cout << "ROAMING END\n";
        break;

    case ROTATING:
        //std::cout << "ROTATING START\n";
        while (
            // Don't reverse
            newdir == baddir
            // and Don't pick a direction that will lead to a wall
            || ls::getTileAt((pos + (Vector2f)newdir * tileSize)) == ls::WALL
            ) {
            
            newdir = directions[(rand() % 4)]; // pick new direction
            if (tries <= 0) {
                newdir = baddir;
            break; 
            }
            tries--;
        }
        _direction = Vector2f(newdir);
        _state = ROTATED;
        //std::cout << "ROTATING END\n";
        break;

    case ROTATED:
        //std::cout << "ROTATED START\n";
        //have we left the waypoint?
        if (LevelSystem::getTileAt(pos) != LevelSystem::WAYPOINT) {
            _state = ROAMING; //yes
        }
        move(_direction * mva); //No
        //std::cout << "ROTATED END\n";
        break;
    }
    //std::cout << "state " << _state << " newdir " << newdir <<" _direction " << _direction << " mva " << mva << std::endl;
    ActorMovementComponent::update(dt);
}
