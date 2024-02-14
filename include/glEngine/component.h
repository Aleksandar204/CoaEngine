#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;

class Component
{
private:
public:
    bool started = false;
    virtual void Start() {}

    virtual void Update() {}
    GameObject* game_object;
};

#endif