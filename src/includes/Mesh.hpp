#pragma once

#include <glad/glad.h>
#include <vector>
// #include "glimac/Geometry.hpp"
#include "glimac/Geometry.hpp"
#include "glimac/common.hpp"

class Mesh {
public:
    // explicit Mesh(const std::vector<glimac::ShapeVertex>& vertices);
    Mesh(GLsizei vertexCount, const glimac::ShapeVertex* vertices);
    explicit Mesh(glimac::Geometry& obj);

    ~Mesh();

    Mesh(const Mesh&)            = delete;
    Mesh& operator=(const Mesh&) = delete;
    Mesh(Mesh&& other) noexcept;
    Mesh& operator=(Mesh&& other) noexcept;

    size_t getVertexCount() const;
    size_t getIndexCount() const;

    void draw() const;

private:
    GLuint m_vao{};
    GLuint m_vbo{};
    GLuint m_ebo{};
    size_t m_indexCount{};
    size_t m_vertexCount{};
};