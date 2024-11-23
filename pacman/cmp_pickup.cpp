//"cmp_pickup.cpp"
#include "cmp_pickup.h"
#include "pacman.h"
#include "cmp_actor_movement.h"



void PickupComponent::update(double) {

    for (auto e : gameScene->getEnts()) {       //every entity in the scene
        if (length(_parent->getPosition() - e->getPosition()) <= 30.0f) {      //within 30.f unit of me
            auto comp = e->getCompatibleComponent<ActorMovementComponent>()[0];           //get the entity ActorMovementComponent, if it has one
                if (comp != NULL && comp != nullptr) {        //if it has one
                  // nom nom
                    comp->setSpeed(comp->getSpeed() * 1.05f);                      //speed the entity up
                        _parent->setForDelete(); //delete myself
                    break;                   //stop looking
                }
        }
    }
}