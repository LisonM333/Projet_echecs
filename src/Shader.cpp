#include "Shader.hpp"
#include <iostream>
#include "glimac/Program.hpp"
#include "glm/fwd.hpp"
#include "glm/gtc/type_ptr.hpp"

Shader::Shader(const glimac::FilePath& appPath, const ShaderFile& shader_files)
    : m_program(glimac::loadProgram(appPath.dirPath() + shader_files.vertexFile, appPath.dirPath() + shader_files.fragmentFile))
{
    // Matrices
    std::cout << "Location uMVPMatrix : " << getUniformLocation("uMVPMatrix") << "\n";
    std::cout << "Location uMVMatrix : " << getUniformLocation("uMVMatrix") << "\n";
    std::cout << "Location uNormalMatrix : " << getUniformLocation("uNormalMatrix") << "\n";

    // Materials
    std::cout << "Location uKd : " << getUniformLocation("uKd") << "\n";
    std::cout << "Location uKs : " << getUniformLocation("uKs") << "\n";
    std::cout << "Location uShininess : " << getUniformLocation("uShininess") << "\n";

    // Illumination
    std::cout << "Location uLightIntensity : " << getUniformLocation("uLightIntensity") << "\n";
    std::cout << "Location uLightDir_vs : " << getUniformLocation("uLightDir_vs") << "\n";
}

void Shader::bind() const
{
    m_program.use();
}

GLint Shader::getUniformLocation(const std::string& name) const
{
    return glGetUniformLocation(m_program.getGLId(), name.c_str());
}

void Shader::sendMat4(const std::string& name, const glm::mat4& matrice) const
{
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrice));
}

void Shader::sendVec3(const std::string& name, const glm::vec3& vector) const
{
    glUniform3fv(getUniformLocation(name), 1, glm::value_ptr(vector));
}

void Shader::sendFloat(const std::string& name, float value) const
{
    glUniform1f(getUniformLocation(name), value);
}