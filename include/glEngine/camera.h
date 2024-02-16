#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

class Camera: public GameObject
{
public:
    float fov;
    Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 rot = glm::vec3(0.0f, 0.0f, 0.0f), float f = 75.0f)
    {
        transform.position = pos;
        transform.rotation = rot;
        transform.size = glm::vec3(1.0f,1.0f,1.0f);
        fov = f;
    }
    glm::mat4 getViewMatrix() const {
        // Calculate the camera's front direction
        glm::vec3 front;
        front.x = cos(glm::radians(transform.rotation.y)) * cos(glm::radians(transform.rotation.x));
        front.y = sin(glm::radians(transform.rotation.x));
        front.z = sin(glm::radians(transform.rotation.y)) * cos(glm::radians(transform.rotation.x));
        front = glm::normalize(front);

        // Calculate the camera's right and up vectors
        glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f))); // Assume world up is y-axis
        glm::vec3 up = glm::normalize(glm::cross(right, front));

        // Construct the view matrix
        return glm::lookAt(transform.position, transform.position + front, up);
    }
};


#endif