#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include <glEngine/model.h>
#include <glEngine/component.h>
#include <glEngine/transform.h>

class GameObject
{
public:
    Model model;
    Transform transform;
    std::vector<Component*> components;
    std::vector<GameObject*> children;
    GameObject* parent = nullptr;
    GameObject(glm::vec3 pos, glm::vec3 rot, glm::vec3 si)
    {
        transform.position = pos;
        transform.rotation = rot;
        transform.size = si;
    }
    GameObject()
    {
        transform.position = glm::vec3(0.0f,0.0f,0.0f);
        transform.rotation = glm::vec3(0.0f,0.0f,0.0f);
        transform.size = glm::vec3(1.0f,1.0f,1.0f);
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

    glm::vec3 getGlobalPosition() {
        glm::mat4 globalTransform = glm::mat4(1.0f);
        if (parent != nullptr) {
            globalTransform = parent->GetGlobalTransform();
        }
        globalTransform = glm::translate(globalTransform, transform.position);
        return glm::vec3(globalTransform[3]);
    }

    // Function to calculate global rotation vector recursively
    glm::vec3 getGlobalRotation() {
        glm::quat globalRotationQuat = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
        if (parent != nullptr) {
            globalRotationQuat = parent->GetGlobalRotationQuat();
        }
        glm::quat localRotationQuat = glm::quat(glm::radians(transform.rotation));
        globalRotationQuat = globalRotationQuat * localRotationQuat;
        return glm::degrees(glm::eulerAngles(globalRotationQuat));
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

private:
    glm::mat4 GetGlobalTransform() {
        glm::mat4 globalTransform = glm::mat4(1.0f);
        if (parent != nullptr) {
            globalTransform = parent->GetGlobalTransform();
        }
        globalTransform = glm::translate(globalTransform, transform.position);
        globalTransform = glm::rotate(globalTransform, glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        globalTransform = glm::rotate(globalTransform, glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        globalTransform = glm::rotate(globalTransform, glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        return globalTransform;
    }

    // Function to calculate global rotation quaternion recursively
    glm::quat GetGlobalRotationQuat() {
        glm::quat globalRotationQuat = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
        if (parent != nullptr) {
            globalRotationQuat = parent->GetGlobalRotationQuat();
        }
        glm::quat localRotationQuat = glm::quat(glm::radians(transform.rotation));
        return globalRotationQuat * localRotationQuat;
    }
};


#endif