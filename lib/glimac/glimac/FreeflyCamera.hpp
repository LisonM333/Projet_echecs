#pragma once

#include "glm/ext/matrix_transform.hpp"

class FreeflyCamera {
private:
  glm::vec3 m_Position; // camera position
  float m_fPhi; // spherical coordinates of F
  float m_fTheta; // spherical coordinates of F
  glm::vec3 m_FrontVector; // F
  glm::vec3 m_LeftVector; // L
  glm::vec3 m_UpVector; // U
  void computeDirectionVectors();

public:
    FreeflyCamera() :m_Position(glm::vec3(0)), m_fPhi(glm::pi<float>()), m_fTheta(0)
    {
        computeDirectionVectors();
    };

    void moveLeft(float t);
    void moveFront(float t);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);
    glm::mat4 getViewMatrix() const;
};