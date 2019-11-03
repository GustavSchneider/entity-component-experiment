#pragma once

#include <memory>

#include "ogl.h"

class texture {
private:
    GLenum texture_type;
    GLuint texture_id;
protected:
    texture(GLenum texture_type) : texture_type(texture_type) {
        glGenTextures(1, &texture_id);
    }
public:
    static std::shared_ptr<texture> genTexture(GLenum texture_type) {
        return std::shared_ptr<texture>(new texture(texture_type),
                                    [=](texture* t) {
                                        glDeleteTextures(1, &t->texture_id);
                                        delete t;
                                    });
    }

    void bind() {
        glBindTexture(texture_type, texture_id);
    }

    void texImage2D(GLint level, GLint internalformat, GLsizei width, GLsizei height,
                    GLint border, GLenum format, GLenum type, const GLvoid * data)
    {
        bind();
        glTexImage2D(texture_type, level, internalformat, width, height, border, format,
                     type, data);
    }

    void texParameteri(GLenum pname, GLint param) {
        bind();
        glTexParameteri(texture_type, pname, param);
    }

    void generateMipmap() {
        bind();
        glGenerateMipmap(texture_type);
    }

    GLuint get_id() {
        return texture_id;
    }
};
