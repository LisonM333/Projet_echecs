#pragma once
// #include <glm/ext/matrix_transform.hpp>
#include "glm/ext/matrix_transform.hpp"

struct TrackballCamera {
private:
    float m_fDistance{};
    float m_fAngleX{};
    float m_fAngleY{};

public:
    TrackballCamera() : m_fDistance(-5) {};
    void
         moveFront(float delta);    // if delta > 0, camera moves forward else backward
    void rotateLeft(float degrees); // lateral rotation
    void rotateUp(float degrees);   // vertical rotation

    glm::mat4 getViewMatrix() const;
};