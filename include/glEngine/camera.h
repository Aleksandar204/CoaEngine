#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

class Camera: public GameObject
{
public:
    float fov = 90;

    glm::mat4 getViewMatrix() {
        return glm::lookAt(getGlobalPosition(), getGlobalPosition() + getGlobalForward(), getGlobalUp());
    }
};


#endif