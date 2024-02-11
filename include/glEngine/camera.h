#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, -position);
        return view;
    }
};


#endif