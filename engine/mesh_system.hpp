#pragma once

#include "base_system.hpp"
#include "mesh_component.hpp"
#include "entity.hpp"

class mesh_system : public base_system<mesh_component> {
public:
    mesh_system(scene* parent_scene, message_system* ms);
    virtual void init();
    virtual void update(float dt);
    virtual void handle_message(msg_set_mesh& message);
};
