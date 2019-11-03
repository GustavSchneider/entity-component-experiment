#pragma once

#include <vector>

#include <ogl.h>
#include <glm/mat4x4.hpp>
#include "entity.hpp"
#include "material.hpp"

enum message_type {
    MSG_BROADCAST = 0,
    MSG_UNICAST
};

class message {
public:
    message_type type;
    entity_id e_id;
};

class msg_render : public message {
};

class msg_set_mesh : public message {
public:
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
};

class msg_set_program : public message {
public:
    GLuint m_program;
};

class msg_set_material : public message {
public:
    material m;
};

/* messages for getting and setting transform data */
class msg_set_transform : public message {
public:
    glm::mat4x4 transform;
};

class msg_get_transform : public msg_set_transform {
public:
    glm::mat4x4* transform;
};

class msg_update_delta_transform : public message {
public:
    glm::mat4x4 delta_transform;
};

class msg_set_resolution : public message {
public:
    glm::ivec2 resolution;
};

class msg_set_camera_values : public message {
public:
    float fov;
    float znear;
    float zfar;
};

class msg_set_main_camera : public message {    
};


