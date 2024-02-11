#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

class Camera
{
private:
    
public:
    glm::vec3 position, rotation;
    float fov;
    Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 rot = glm::vec3(0.0f, 0.0f, 0.0f),float f = 75.0f)
    {
        position = pos;
        rotation = rot;
        fov = f;
    }

    glm::mat4 getViewMatrix()
    {
        glm::quat quaternion = glm::quat(glm::radians(rotation));
        glm::mat4 rotationMatrix = glm::toMat4(quaternion);
        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), -position);
        glm::mat4 viewMatrix = rotationMatrix * translationMatrix;

        return viewMatrix;
    }
};


#endif