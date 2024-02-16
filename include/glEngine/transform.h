#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transform
{
public:
    glm::vec3 position, rotation, size;

    glm::vec3 forward()
    {
        glm::vec3 front;
        front.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
        front.y = sin(glm::radians(rotation.x));
        front.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
        front = glm::normalize(front);
        return front;
    }
    glm::vec3 up()
    {
        glm::vec3 front;
        front.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
        front.y = sin(glm::radians(rotation.x));
        front.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
        front = glm::normalize(front);

        glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
        glm::vec3 up = glm::normalize(glm::cross(right, front));
        return up;
    }
    glm::vec3 right()
    {
        glm::vec3 front;
        front.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
        front.y = sin(glm::radians(rotation.x));
        front.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
        front = glm::normalize(front);

        glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
        return right;
    }   
};
#endif