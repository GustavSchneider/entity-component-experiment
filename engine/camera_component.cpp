#include "camera_component.hpp"

camera_component::camera_component(entity_id id)
    : base_component(id)
{
    glGenTextures(num_textures, m_textures);
    glGenFramebuffers(1, &m_gbuffer_fbo);
    glGenFramebuffers(1, &m_finalize_fbo);
}

camera_component::~camera_component() {
    glDeleteFramebuffers(1, &m_gbuffer_fbo);
    glDeleteTextures(num_textures, m_textures);
}

void camera_component::init() {
    /* Creating textures and setting params */
    /* -1 because we want to handle depth texture individually */
    for (size_t i = 0; i < num_textures - 1; i++) {
        glBindTexture(GL_TEXTURE_2D, m_textures[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_resolution.x, m_resolution.y, 0,
                     GL_RGBA, GL_FLOAT, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

    glBindTexture(GL_TEXTURE_2D, m_textures[depth_texture]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, m_resolution.x, m_resolution.y, 0,
                 GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    
    /* Setting up gbuffer framebuffer */
    glBindFramebuffer(GL_FRAMEBUFFER, m_gbuffer_fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                           m_textures[albedo_texture], 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D,
                           m_textures[material_texture], 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D,
                           m_textures[normal_texture], 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D,
                           m_textures[position_texture], 0);    
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_textures[depth_texture], 0);
    
    GLenum gbuffer_draw_buffers[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1,
                                     GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3};
    glDrawBuffers(4, gbuffer_draw_buffers);
    
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {      
        fprintf(stderr, "G-Buffer Framebuffer error %i\n",
                glCheckFramebufferStatus(GL_FRAMEBUFFER));
        exit(1);
    }

    /* Setup finalize framebuffer */
    glBindFramebuffer(GL_FRAMEBUFFER, m_finalize_fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                           m_textures[final_texture], 0);    
    GLenum finalize_draw_buffers[] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, finalize_draw_buffers);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {      
        fprintf(stderr, "Finalize Framebuffer error %i\n",
                glCheckFramebufferStatus(GL_FRAMEBUFFER));
        exit(1);
    }
}

bool camera_component::initialized() {
    return m_initialized;
}
