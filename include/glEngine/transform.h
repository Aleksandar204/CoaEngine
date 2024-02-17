#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>


class Transform
{
public:
    glm::vec3 position, rotation, size;

    glm::vec3 forward()
    {
        glm::vec4 f = glm::toMat4(glm::quat(glm::radians(rotation))) * glm::vec4(0,0,-1.0f,1.0f);
        return glm::normalize(glm::vec3(f.x,f.y,f.z));
    }
    glm::vec3 up()
    {
        glm::vec3 front = forward();
        glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
        glm::vec3 up = glm::normalize(glm::cross(right, front));
        return up;
    }
    glm::vec3 right()
    {
        glm::vec3 front = forward();
        glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
        return right;
    }   
};
#endif