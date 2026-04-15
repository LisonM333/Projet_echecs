#pragma once
#include <glad/glad.h>

class Renderer {
public:
    Renderer(unsigned int width, unsigned int height);
    ~Renderer();
    Renderer(const Renderer&)            = delete;
    Renderer& operator=(const Renderer&) = delete;
    Renderer(Renderer&&)                 = default;
    Renderer& operator=(Renderer&&)      = default;

    void   bind() const;
    void   unbind() const;
    GLuint texture() const { return m_texture; };

private:
    GLuint       m_fbo{};
    GLuint       m_texture{};
    GLuint       m_rbo{};
    unsigned int m_width{};
    unsigned int m_height{};
};