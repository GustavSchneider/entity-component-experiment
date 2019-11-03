#include "mesh_renderer_system.hpp"
#include "scene.hpp"
#include <ogl.h>
    
mesh_renderer_system::mesh_renderer_system(scene* parent_scene, message_system* ms)
    : base_system(parent_scene, ms) {
    m_message_system->register_handler<msg_set_program>(this);
    m_message_system->register_handler<msg_render>(this);
    //m_message_system->register_handler<msg_set_material>(this);
};
    
void mesh_renderer_system::init() {
    
}

void mesh_renderer_system::update(float dt) {
}

void mesh_renderer_system::render(mesh_renderer_component& comp) {
    auto& mesh_system = parent_scene->m_mesh_system;
    auto& transform_system = parent_scene->m_transform_system;
    
    if (!transform_system.has_component(comp.get_entity_ptr())) return;
    if (!mesh_system.has_component(comp.get_entity_ptr())) return;
    auto& mesh_comp = mesh_system.get_component(comp.get_entity_ptr());
    if (!mesh_comp.has_mesh()) return;    
    auto& transform_comp = transform_system.get_component(comp.get_entity_ptr());
    auto& transform = transform_comp.m_transform;
    //has material?

    //This should be cleaned up
    glUseProgram(comp.m_program);        
    glUniform4f(glGetUniformLocation(comp.m_program, "color"), .7, .3, 0., 1.);
    GLuint model_matrix_loc = glGetUniformLocation(comp.m_program, "model_matrix");
    glUniformMatrix4fv(model_matrix_loc, 1, GL_TRUE, &transform[0][0]);
        
    glBindVertexArray(mesh_comp.m_vao);
    glDrawElements(GL_TRIANGLES, mesh_comp.m_num_indices, GL_UNSIGNED_INT, 0);
}

void mesh_renderer_system::handle_message(msg_render& message) {
    if (message.type == MSG_UNICAST) {
        if (has_component(message.e_id)) {
            render(m_component_array[m_component_map[message.e_id]]);
        }
    } else {   
        for (mesh_renderer_component& c : m_component_array) {
            render(c);
        }
    }
}

void mesh_renderer_system::handle_message(msg_set_program& message) {
    if (m_component_map.find(message.e_id) == m_component_map.end()) {
        add_component(message.e_id);
    }
    auto& comp = get_component(message.e_id);
    comp.m_program = message.m_program;
    printf("received program %i\n", message.m_program);
}
