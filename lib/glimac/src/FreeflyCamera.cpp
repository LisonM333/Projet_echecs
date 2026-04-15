#include "glimac/FreeflyCamera.hpp"
#include "glm/gtc/constants.hpp"


// compute front, left and up vector
void FreeflyCamera::computeDirectionVectors(){
    // front
    m_FrontVector = glm::vec3(
        glm::cos(m_fTheta)*glm::sin(m_fPhi),
        glm::sin(m_fTheta),
        glm::cos(m_fTheta)*glm::cos(m_fPhi));

    // left
    m_LeftVector = glm::vec3(
        glm::sin(m_fPhi + glm::pi<float>()/2),
        0,
        glm::cos(m_fPhi + glm::pi<float>()/2));

    // up
    m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
};

void FreeflyCamera::moveLeft(float t){
    m_Position += t*m_LeftVector;
};

void FreeflyCamera::moveFront(float t){
    m_Position += t*m_FrontVector;
};

void FreeflyCamera::rotateLeft(float degrees) {
    m_fPhi += glm::radians(degrees);
};

void FreeflyCamera::rotateUp(float degrees) {
    m_fTheta += glm::radians(degrees);
};

glm::mat4 FreeflyCamera::getViewMatrix() const {
    glm::vec3 pointOfView {m_Position + m_FrontVector};
    return glm::lookAt(m_Position, pointOfView,m_UpVector);
}
