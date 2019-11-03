#pragma once

#include "base_component.hpp"
#include "material.hpp"
#include <program.hpp>

class mesh_renderer_component : public base_component {
public:
    GLuint m_program;
    material m_material;
    
    mesh_renderer_component(entity_id id) : base_component(id) {}
    
    virtual void init();
    virtual void update(float dt);
};
