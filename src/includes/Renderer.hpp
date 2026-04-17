#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Shader.hpp"
#include "glimac/TrackballCamera.hpp"
#include "mesh.hpp"

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

    // void setup_frame(const Camera& camera, float width, float height, const glm::vec3& worldLightDir);
    void setup_frame(Shader& shader, const TrackballCamera& camera, float screen_width, float screen_height, const glm::vec3& worldLightDir);
    // void renderMesh(Shader& shader, const Mesh& mesh, const glm::mat4& modelMatrix, bool calls_draw);

private:
    GLuint       m_fbo{};
    GLuint       m_texture{};
    GLuint       m_rbo{};
    unsigned int m_width{};
    unsigned int m_height{};

    glm::mat4 m_viewMatrix{};
    glm::mat4 m_projMatrix{};
};