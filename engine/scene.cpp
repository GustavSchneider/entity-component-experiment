#include "scene.hpp"
#include "entity.hpp"

scene::scene(glm::ivec2 resolution) :
    m_camera_system(this, &m_message_system),
    m_mesh_system(this, &m_message_system),
    m_mesh_renderer_system(this, &m_message_system),
    m_transform_system(this, &m_message_system)
{
    msg_set_resolution res_msg;
    res_msg.resolution = resolution;
    m_message_system.dispatch_message(res_msg);
    
    auto vert_shader = shader::compile("shaders/vs_simple.glsl", GL_VERTEX_SHADER);
    auto frag_shader = shader::compile("shaders/fs_simple.glsl", GL_FRAGMENT_SHADER);
    m_default_program = program::create();
    m_default_program->attachShader(vert_shader);
    m_default_program->attachShader(frag_shader);
    m_default_program->link();

    entity_id eid = create_entity();
    
    msg_set_mesh m0;
    m0.e_id = eid;
    m0.vertices = {.5, .5, 0., -.5, .5, 0., .5, -.5, 0.};
    m0.indices = {0, 1, 2};
    m_message_system.dispatch_message(m0);

    msg_set_program m1;
    m1.e_id = eid;
    m1.m_program = m_default_program->get_id();
    m_message_system.dispatch_message(m1);    

    msg_set_transform m2;
    m2.e_id = eid;
    m_message_system.dispatch_message(m2);

    entity_id cam = create_entity();
    m_transform_system.add_component(cam);
    m_camera_system.add_component(cam);
    auto& comp = m_camera_system.get_component(cam);
    comp.m_active = true;
}

void scene::update(float dt) {
    //m_mesh_renderer_system.update(dt);
    m_camera_system.update(dt);
}

void scene::remove_entity(entity_id id) {
    m_free_list.push_back(id);
    m_entity_count--;
    //must remove all components aswell
}
    
entity_id scene::create_entity()
{
    m_entity_count++;
    if (!m_free_list.empty()) {
        entity_id id = m_free_list[0];
        m_free_list.erase(m_free_list.begin());
        return id;
    }
    return m_id_counter++;
}

size_t scene::entity_count() {
    return m_entity_count;
}

