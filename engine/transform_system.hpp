#pragma once

#include "transform_component.hpp"
#include "base_system.hpp"
#include "messages.hpp"

class transform_system : public base_system<transform_component> {
public:
    transform_system(scene* parent_scene, message_system* ms);
    virtual void init();
    virtual void update(float dt);

    virtual void handle_message(msg_set_transform& message);
    virtual void handle_message(msg_get_transform& message);
    virtual void handle_message(msg_update_delta_transform& message);
};
