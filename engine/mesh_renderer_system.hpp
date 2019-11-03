#pragma once

#include "base_system.hpp"
#include "mesh_renderer_component.hpp"
#include "camera_component.hpp"
#include "entity.hpp"

class mesh_renderer_system : public base_system<mesh_renderer_component> {
private:
    void render(mesh_renderer_component& comp);
public:
    mesh_renderer_system(scene* parent_scene, message_system* ms);
    
    virtual void init();
    virtual void update(float dt);

    virtual void handle_message(msg_render& message);
    virtual void handle_message(msg_set_program& message);
};
