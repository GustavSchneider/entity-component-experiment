#pragma once
#include "base_system.hpp"
#include "particle_system_component.hpp"
class particle_system_system : public base_system<particle_system_component> {
public:
    virtual void init() {}
    virtual void update(float dt) {}
}
