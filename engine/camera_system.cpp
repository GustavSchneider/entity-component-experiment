#include "camera_system.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include "scene.hpp"

camera_system::camera_system(scene* parent_scene, message_system* ms)
    : base_system(parent_scene, ms)
{
    glGenBuffers(1, &m_matrix_uniform_buffer);
    glBindBuffer(GL_UNIFORM_BUFFER, m_matrix_uniform_buffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(camera_data_t), nullptr, GL_DYNAMIC_DRAW);
    //ms->register_handler<msg_set_fov>(this);
    //ms->register_handler<msg_set_exposure>(this);
    ms->register_handler<msg_set_resolution>(this);
}

camera_system::~camera_system() {

}

void camera_system::init() {

}

void camera_system::update(float dt) {
    auto& transform_system = parent_scene->m_transform_system;
    for (camera_component& comp : m_component_array) {
        if (comp.initialized() == false) {
            comp.m_resolution = m_resolution;
            comp.init();
        }
        entity_id e_id = comp.get_entity_ptr();
        if (!comp.m_active) continue;
        if (!transform_system.has_component(e_id)) continue;
        glm::mat4x4 transform = transform_system.get_component(e_id).m_transform;

        camera_data_t camera_data;
        auto lookat =  glm::lookAt(glm::vec3(0, 0, -1.),
                                   glm::vec3(0, 0, 1),
                                   glm::vec3(0, 1, 0));
        auto view_matrix = lookat * transform;
        auto projection_matrix = glm::perspective(comp.m_fov, comp.m_aspect,
                                                         comp.m_znear, comp.m_zfar);

        glNamedBufferSubData(m_matrix_uniform_buffer, 0, sizeof(glm::mat4x4),
                             &view_matrix[0][0]);
        glNamedBufferSubData(m_matrix_uniform_buffer, 64, sizeof(glm::mat4x4),
                             &projection_matrix[0][0]);
        glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_matrix_uniform_buffer);

        //glBindFramebuffer(GL_FRAMEBUFFER, comp.m_gbuffer_fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        msg_render mr;
        m_message_system->dispatch_message(mr);

        //finalize the render
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

// void camera_system::handle_message(msg_set_fov& message) {

// }

// void camera_system::handle_message(msg_set_exposure& message) {

// }

void camera_system::handle_message(msg_set_resolution& message) {
    printf("resolution changed\n");
    /* When the resolution changes we have to re-create all the 
       textures of the fbos */
    m_resolution = message.resolution;
    for (auto& comp : m_component_array) {
        comp.m_resolution = message.resolution;
        comp.init();
    }
}
