//"cmp_pickup.h"
#pragma once
#include <ecm.h>
#include "../lib_tile_level_loader/LevelSystem.h"



class PickupComponent : public Component {
private:
    float points;
public:
    PickupComponent(Entity* p, bool big);
    PickupComponent() = delete;
    void update(double dt) override;
    void render() override {};
};