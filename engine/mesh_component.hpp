#pragma once

#include <vector>
#include <ogl.h>

#include "base_component.hpp"

class mesh_component : public base_component {
public:
    GLuint m_vao;
    enum {m_vertex_vbo, m_indice_vbo, m_num_vbos};
    GLuint m_vbos[m_num_vbos];
    bool m_has_mesh;
    GLuint m_num_indices;
    
    mesh_component(entity_id id);
    ~mesh_component();
    void set_mesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices);
    void clear_mesh();
    bool has_mesh();
    GLuint num_indices();
    GLuint get_vao();
};
