#include "mesh_component.hpp"

mesh_component::mesh_component(entity_id id)
    : base_component(id)
{
}

mesh_component::~mesh_component() {
    if (m_has_mesh) {
        clear_mesh();
    }
}

void mesh_component::clear_mesh() {
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(m_num_vbos, m_vbos);    
}

void mesh_component::set_mesh(const std::vector<GLfloat>& vertices,
                              const std::vector<GLuint>& indices)
{
    if (m_has_mesh) {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(m_num_vbos, m_vbos);
    }
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(m_num_vbos, m_vbos);
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbos[m_vertex_vbo]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), vertices.data(),
                 GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbos[m_indice_vbo]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(),
                 indices.data(), GL_STATIC_DRAW);
    glBindVertexArray(0);
    
    m_num_indices = indices.size();
    m_has_mesh = true;
}

bool mesh_component::has_mesh() {
    return m_has_mesh;
}

GLuint mesh_component::num_indices() {
    return m_num_indices;
}

GLuint mesh_component::get_vao() {
    return m_vao;
}

