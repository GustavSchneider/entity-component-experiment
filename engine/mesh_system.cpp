#include "mesh_system.hpp"
#include "message_system.hpp"

mesh_system::mesh_system(scene* parent_scene, message_system* ms)
    : base_system(parent_scene, ms) {
    ms->register_handler<msg_set_mesh>(this);
}

void mesh_system::init() {

}

void mesh_system::update(float dt) {

}

void mesh_system::handle_message(msg_set_mesh& message) {    
    entity_id e_id = message.e_id;
    if (!has_component(e_id)) {
        add_component(e_id);
    }
    mesh_component& comp =  m_component_array[m_component_map[e_id]];
    if ( m_component_array[m_component_map[e_id]].has_mesh() ){
        comp.clear_mesh();
    }    
    comp.set_mesh(message.vertices, message.indices);
}
