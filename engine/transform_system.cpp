#include "transform_system.hpp"
#include "messages.hpp"
#include "message_system.hpp"

transform_system::transform_system(scene* parent_scene, message_system* ms)
    : base_system(parent_scene, ms)
{
    ms->register_handler<msg_set_transform>(this);
    ms->register_handler<msg_get_transform>(this);
    ms->register_handler<msg_update_delta_transform>(this);
}

void transform_system::init() {

}

void transform_system::update(float dt) {
    
}

void transform_system::handle_message(msg_set_transform& message) {
    entity_id e_id = message.e_id;
    if (!has_component(e_id)) {
        add_component(e_id);
    }
    transform_component& comp = get_component(e_id);
    comp.m_transform = message.transform;
}

void transform_system::handle_message(msg_get_transform& message) {    
    assert(has_component(message.e_id));
    transform_component& comp = get_component(message.e_id);
    message.transform = &comp.m_transform;
}

void transform_system::handle_message(msg_update_delta_transform& message) {
    assert(has_component(message.e_id));
    transform_component& comp = get_component(message.e_id);
    comp.m_transform += message.delta_transform;
}
