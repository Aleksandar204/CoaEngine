#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;
class Scene;

class Component
{
private:
public:
    bool started = false;
    virtual void Start() {}

    virtual void Update() {}
    GameObject* game_object;
    Scene* current_scene;
};

#endif