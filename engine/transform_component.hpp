#pragma once

#include "base_component.hpp"
#include <glm/mat4x4.hpp>

class transform_component : public base_component {
public:
    glm::mat4x4 m_transform;
    transform_component(entity_id id) : base_component(id) {}    
};
