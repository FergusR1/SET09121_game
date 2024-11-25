//"cmp_pickup.cpp"
#include "cmp_pickup.h"
#include "pacman.h"
#include "cmp_actor_movement.h"


PickupComponent::PickupComponent(Entity* p, bool big) : Component(p) {
    points = big ? 5 : 1;
}

void PickupComponent::update(double) {

    for (auto e : gameScene->getEnts()) {       //every entity in the scene
        if (length(_parent->getPosition() - e->getPosition()) <= 20.0f) {      //within 30.f unit of me
            //std::cout << "PRE COMP THING" << std::endl;
            auto compList = e->getCompatibleComponent<ActorMovementComponent>();           //get the entity ActorMovementComponent, if it has one
            
                if (compList.size() > 0) {        //if it has one
                  // nom nom
                    auto comp = compList[0];
                    float speed = comp->getSpeed();
                    std::cout << "speed = " << speed << " ";
                    speed *= (0.01f*points + 1);
                    if (speed > 300.f) { speed = 300.f; }
                    if (speed < 100.f) { speed = 100.f; }
                    std::cout << "-> new speed = " << speed << std::endl;

                    comp->setSpeed(speed);                      //speed the entity up
                        _parent->setForDelete(); //delete myself
                    break;                   //stop looking
                }
        }
    }
}