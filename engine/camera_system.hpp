#pragma once

#include <ogl.h>

#include "base_system.hpp"
#include "camera_component.hpp"

class camera_system : public base_system<camera_component> {
private:
    struct camera_data_t {
        glm::mat4x4 view_matrix;
        glm::mat4x4 projection_matrix;        
    };
    GLuint m_matrix_uniform_buffer;
    glm::ivec2 m_resolution;
public:
    camera_system(scene* parent_scene, message_system* ms);  
    ~camera_system();
    virtual void init();
    virtual void update(float dt);
    //virtual void handle_message(msg_set_fov& message);
    //virtual void handle_message(msg_set_exposure& message);
    virtual void handle_message(msg_set_resolution& message);
};
