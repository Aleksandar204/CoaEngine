#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

#include <vector>

#include <glEngine/model.h>
#include <glEngine/component.h>

class GameObject
{
public:
    Model* model = nullptr;
    std::vector<Component*> components;
    std::vector<GameObject*> children;
    GameObject* parent = nullptr;
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    GameObject(glm::vec3 pos, glm::vec3 rot, glm::vec3 si)
    {
        modelMatrix = glm::translate(modelMatrix, pos);
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rot.y), glm::vec3(0.0f,1.0f,0.0f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rot.x), glm::vec3(1.0f,0.0f,0.0f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rot.z), glm::vec3(0.0f,0.0f,1.0f));
        modelMatrix = glm::scale(modelMatrix,si);
    }
    GameObject()
    {
        
    }

    void addComponent(Component* component)
    {
        component->game_object = this;
        components.push_back(component);
    }

    void addChild(GameObject* child)
    {
        child->parent = this;
        children.push_back(child);
    }

    void updateAndStart()
    {
        for (unsigned int i = 0; i < components.size(); i++)
        {
            if(!components[i]->started)
            {
                
                components[i]->Start();
                components[i]->started = true;
            }
            components[i]->Update();
        }
        // for (unsigned int i = 0; i < children.size(); i++)
        // {
        //     children[i]->updateAndStart();
        // }
        
    }
    void getAllChildren(std::vector<GameObject*> *gos)
    {
        for (unsigned int i = 0; i < children.size(); i++)
        {
            gos->push_back(children[i]);
            children[i]->getAllChildren(gos);
        }
    }

    glm::mat4 getGlobalModelMatrix()
    {
        glm::mat4 globalMat = modelMatrix;
        GameObject* curr = parent;
        while (curr != nullptr)
        {
            globalMat = curr->modelMatrix * globalMat;
            curr = curr->parent;
        }
        return globalMat;
    }
    glm::vec3 getGlobalPosition()
    {
        return glm::vec3(getGlobalModelMatrix()[3]);
    }
    glm::quat getGlobalRotation()
    {
        return glm::quat(glm::mat3(getGlobalModelMatrix()));
    }
    glm::vec3 getGlobalScale()
    {
        return glm::vec3(glm::length(getGlobalModelMatrix()[0]), glm::length(getGlobalModelMatrix()[1]), glm::length(getGlobalModelMatrix()[2]));
    }
    glm::vec3 getGlobalForward()
    {
        // glm::vec4 f =  glm::vec4(0,0,1.0f,-1.0f) * glm::toMat4(glm::quat(glm::radians(rotation)));
        glm::vec4 f = glm::vec4(0.0f,0.0f,-1.0f,1.0f);
        glm::mat4 rotmat = glm::toMat4(getGlobalRotation());
        f = rotmat * f;
        return glm::normalize(glm::vec3(f.x,f.y,f.z));
    }
    glm::vec3 getGlobalUp()
    {
        glm::vec3 front = getGlobalForward();
        glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
        glm::vec3 up = glm::normalize(glm::cross(right, front));
        return up;
    }
    glm::vec3 getGlobalRight()
    {
        glm::vec3 front = getGlobalForward();
        glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
        return right;
    }

    void translateLocal(glm::vec3 translation)
    {
        modelMatrix = glm::translate(modelMatrix, translation);
    }

    void rotateLocalEuler(glm::vec3 rot)
    {
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rot.y), glm::vec3(0.0f,1.0f,0.0f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rot.x), glm::vec3(1.0f,0.0f,0.0f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rot.z), glm::vec3(0.0f,0.0f,1.0f));
    }

    void scaleLocal()
    {

    }

private:
    
};
#endif