#pragma once

#include "base_component.hpp"

#include <ogl.h>
#include <algorithm>

class particle_system_component : public base_component {
public:
    particle_system_component(entity_id id) : base_component(id) {}
    
    float point[] = {0.0f, 0.0f, 0.0f};
    GLuint m_vao;
    GLuint m_points_vbo;
    GLuint m_current_buffer;
    GLuint m_previous_buffer;

    virtual void init() {}
    virtual void update(float dt) {}
};

//transform feedback simple system
//position (point)
//life time (if life time is 0 a new particle is generated)
//color (could just randomly generate when created)
