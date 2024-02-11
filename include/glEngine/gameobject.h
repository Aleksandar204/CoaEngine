#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glEngine/model.h>

class GameObject
{
public:
    glm::vec3 position, rotation, size;
    Model model;

    GameObject(glm::vec3 pos, glm::vec3 rot, glm::vec3 si)
    {
        position = pos;
        rotation = rot;
        size = si;
    }
    GameObject()
    {
        position = glm::vec3(0.0f,0.0f,0.0f);
        rotation = glm::vec3(0.0f,0.0f,0.0f);
        size = glm::vec3(1.0f,1.0f,1.0f);
    }
    void draw()
    {
        model.draw();
    }

    void updateAndStart()
    {
        
        if(!startCalled)
        {
            Start();
            startCalled = true;
        }
        Update();
    }

    virtual void Start() {}

    virtual void Update() {}

private:
    bool startCalled = false;
};
#endif