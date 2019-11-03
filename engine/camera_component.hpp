#pragma once

#include <glm/mat4x4.hpp>

#include <ogl.h>
#include "base_component.hpp"

class camera_component : public base_component {
private:
    bool m_initialized = false;
    void framebuffer_setup();
public:
    bool m_active;
    glm::ivec2 m_resolution;
    float m_fov = 45;
    float m_aspect = 9.0f / 16.0f;
    float m_exposure = 1.0;
    float m_znear = 1.0f;
    float m_zfar = 10.0f;

    GLuint m_gbuffer_fbo;
    GLuint m_finalize_fbo;
    /* The depth_texture has to be the last one in this enum */
    enum texture_type {albedo_texture = 0,
                       material_texture,
                       normal_texture,
                       position_texture,
                       final_texture,
                       depth_texture,
                       num_textures}; 
    GLuint m_textures[num_textures];
   
    camera_component(entity_id id);    
    ~camera_component();
    virtual void init();
    bool initialized();
    void set_resolution(glm::ivec2 resolution);
};
