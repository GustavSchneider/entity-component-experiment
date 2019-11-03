#pragma once
#include "entity.hpp"
#include "mesh_renderer_system.hpp"
#include "message_system.hpp"
#include "camera_system.hpp"
#include "mesh_system.hpp"
#include "mesh_renderer_component.hpp"
#include "transform_system.hpp"

#include "../gl/program.hpp"

#include <vector>

class scene {
private:
    entity_id m_id_counter = 1;
    std::vector<entity_id> m_free_list;
    std::shared_ptr<program> m_default_program;
    size_t m_entity_count = 0;

    entity_id main_camera;
public:
    message_system m_message_system;
    camera_system m_camera_system;
    mesh_system m_mesh_system;
    mesh_renderer_system m_mesh_renderer_system;
    transform_system m_transform_system;    
    
    scene(glm::ivec2 resolution);

    void update(float dt);

    entity_id create_entity();
    void remove_entity(entity_id id);
    size_t entity_count();
};
