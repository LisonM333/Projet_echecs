#include "mesh.hpp"
#include "glimac/Geometry.hpp"
#include "glimac/common.hpp"

// Mesh::Mesh(const std::vector<glimac::ShapeVertex>& vertices) : m_vertexCount(vertices.size())
Mesh::Mesh(GLsizei const vertexCount, const glimac::ShapeVertex* vertices) : m_vertexCount(vertexCount)
{
    /* VBO */
    /* Create VBO */
    glGenBuffers(1, &m_vbo);              // generate vbo with an id
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo); // bind vbo

    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(m_vertexCount * sizeof(glimac::ShapeVertex)), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind vbo

    /* VAO */
    /* Create VAO */
    glGenVertexArrays(1, &m_vao);

    glBindVertexArray(m_vao); // bind vao

    /* Attributes activation */

    const GLuint VERTEX_ATTR_POSITION = 0;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);

    const GLuint VERTEX_ATTR_NORMAL = 1;
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);

    const GLuint VERTEX_ATTR_TEXCOORDS = 2;
    glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);

    // Bind VBO on GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    // Tell how to use data
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (GLvoid*)offsetof(glimac::ShapeVertex, position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (GLvoid*)offsetof(glimac::ShapeVertex, normal));
    glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (GLvoid*)offsetof(glimac::ShapeVertex, texCoords));

    // Unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* Debind VAO */
    glBindVertexArray(0);
}

Mesh::Mesh(glimac::Geometry& obj) : m_indexCount(obj.getIndexCount()), m_vertexCount(obj.getVertexCount())
{
    /* VBO */
    /* Create VBO */
    glGenBuffers(1, &m_vbo);              // generate vbo with an id
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo); // bind vbo

    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(obj.getVertexCount() * sizeof(glimac::Geometry::Vertex)), obj.getVertexBuffer(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind vbo

    /* EBO */
    /* Create EBO*/
    glGenBuffers(1, &m_ebo); // generate ebo with an id

    /* VAO */
    /* Create VAO */
    glGenVertexArrays(1, &m_vao);

    glBindVertexArray(m_vao); // bind vao

    /* Attributes activation */

    const GLuint VERTEX_ATTR_POSITION = 0;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);

    const GLuint VERTEX_ATTR_NORMAL = 1;
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);

    const GLuint VERTEX_ATTR_TEXCOORDS = 2;
    glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);

    // Bind VBO on GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    // Tell how to use data
    // position
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::Geometry::Vertex), (GLvoid*)offsetof(glimac::Geometry::Vertex, m_Position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::Geometry::Vertex), (GLvoid*)offsetof(glimac::Geometry::Vertex, m_Normal));
    glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::Geometry::Vertex), (GLvoid*)offsetof(glimac::Geometry::Vertex, m_TexCoords));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo); // bind ebo
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, obj.getIndexCount() * sizeof(unsigned int), obj.getIndexBuffer(), GL_STATIC_DRAW);

    // Unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* Debind VAO */
    glBindVertexArray(0);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // unbind ebo

    for (size_t i = 0; i < obj.getMeshCount(); ++i)
    {
        m_subMeshes.push_back(obj.getMeshBuffer()[i]);
    }

    m_materials = obj.getMaterials();
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
}

void Mesh::draw() const
{
    glBindVertexArray(m_vao);

    if (m_ebo != 0)
    {
        glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
    }
    else
    {
        glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(m_vertexCount));
    }
    glBindVertexArray(0);
}

Mesh::Mesh(Mesh&& other) noexcept : m_vao(other.m_vao), m_vbo(other.m_vbo), m_ebo(other.m_ebo), m_indexCount(other.m_indexCount), m_vertexCount(other.m_vertexCount), m_subMeshes(std::move(other.m_subMeshes)), m_materials(std::move(other.m_materials))
{
    other.m_vao = 0;
    other.m_vbo = 0;
    other.m_ebo = 0;
}

Mesh& Mesh::operator=(Mesh&& other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);

    m_vao         = other.m_vao;
    m_vbo         = other.m_vbo;
    m_ebo         = other.m_ebo;
    m_indexCount  = other.m_indexCount;
    m_vertexCount = other.m_vertexCount;
    m_subMeshes   = other.m_subMeshes;
    m_materials   = other.m_materials;

    other.m_vao = 0;
    other.m_vbo = 0;
    other.m_ebo = 0;

    return *this;
}

size_t Mesh::getVertexCount() const
{
    return m_vertexCount;
}

size_t Mesh::getIndexCount() const
{
    return m_indexCount;
}

std::vector<glimac::Geometry::Mesh> Mesh::getSubMeshes() const
{
    return m_subMeshes;
}

std::vector<glimac::Geometry::Material> Mesh::getMaterials() const
{
    return m_materials;
}

GLuint Mesh::getVAO() const
{
    return m_vao;
};

