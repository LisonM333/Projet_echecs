#pragma once

#include <glad/glad.h>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "glimac/TrackballCamera.hpp"
#include "glm/fwd.hpp"

struct ShaderFile {
    glimac::FilePath vertexFile;
    glimac::FilePath fragmentFile;
};

class Shader {
public:
    Shader(const glimac::FilePath& appPath, const ShaderFile& shader_files);
    void bind() const;
    // void unbind() const;

    GLint getUniformLocation(const std::string& name) const;
    void  sendMat4(const std::string& name, const glm::mat4& matrice) const;
    void  sendVec3(const std::string& name, const glm::vec3& vector) const;
    void  sendFloat(const std::string& name, float value) const;

private:
    glimac::Program m_program;
};