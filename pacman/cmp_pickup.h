//"cmp_pickup.h"
#pragma once
#include <ecm.h>
#include "../lib_tile_level_loader/LevelSystem.h"



class PickupComponent : public Component {
public:
    PickupComponent::PickupComponent(Entity* p);
    PickupComponent() = delete;
    void update(double dt) override;
};