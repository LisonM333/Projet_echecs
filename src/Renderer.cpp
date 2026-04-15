#include "Renderer.hpp"
#include <iostream>

Renderer::Renderer(unsigned int width, unsigned int height)
    : m_width(width), m_height(height)
{
    /* Texture */

    // create color attachment texture
    //   unsigned int texture{};
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture); // bind texture

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<GLsizei>(width), static_cast<GLsizei>(height), 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr); // send texture

    // filters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0); // unbind texture

    /* Render Buffer Object */

    // create rbo for depth and stencil attachments

    glGenRenderbuffers(1, &m_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo); // bind rbo

    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, static_cast<GLsizei>(width), static_cast<GLsizei>(height)); // attach depth and stencil

    glBindRenderbuffer(GL_RENDERBUFFER, 0); // unbind rbo

    /* FrameBuffer Object */

    // create fbo
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo); // bind fbo

    // attachements to fbo
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

    // check if fbo complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cerr << "AAAAAAAAAAAAAAAAAAAAAA!\n"; // ERROR::FRAMEBUFFER:: Framebuffer is not complete!

    glBindFramebuffer(GL_FRAMEBUFFER, 0); // unbind fbo
}

Renderer::~Renderer()
{
    glDeleteFramebuffers(1, &m_fbo);
    glDeleteTextures(1, &m_texture);
    glDeleteRenderbuffers(1, &m_rbo);
}

void Renderer::bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glViewport(0, 0, static_cast<GLint>(m_width), static_cast<GLint>(m_height));
    glClearColor(.5f, 1.f, .5f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::unbind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
