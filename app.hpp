#pragma once

#include <ogl.h>
#include <iostream>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdlib>

#include "engine/scene.hpp"
#include "gl/program.hpp"

class app {
private:
    glm::ivec2 m_res;
    glm::vec2 m_cursor_pos;
public:
    void set_cursor_pos(float xpos, float ypos) {
        m_cursor_pos = glm::vec2(xpos/m_res.x, ypos/m_res.y) * 2.f -
            glm::vec2(1);
    }
    
    app(glm::ivec2 res)
        : m_res(res)
    {

    }

    void resize(int width, int height) {
        m_res = glm::ivec2(width, height);
    }
    
    void draw(float dt) {
	
    }
};
