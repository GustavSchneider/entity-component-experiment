#pragma once

#include <ogl.h>

enum texture_type {
    TEXTURE_NONE,
    TEXTURE_ALBEDO = 1,
    TEXTURE_ROUGHNESS = 1 << 1,
    TEXTURE_NORMAL_MAP = 1 << 2
};

class material {
public:
    texture_type texture_flags;
    GLuint albedo_texture;
    GLuint metallic_texture;
    GLuint roughness_texture;
    GLuint normal_map_texture;
    bool has_texture(texture_type type) {
        return (texture_flags & type) != TEXTURE_NONE;
    }
};
