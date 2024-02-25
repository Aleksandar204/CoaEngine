#ifndef SCENE_H
#define SCENE_H

#include <glEngine/gameobject.h>
#include <glEngine/camera.h>

#include <vector>

class Scene
{
private:

public:
    std::string name;
    std::vector<GameObject*> game_objects = {&cam};
    Camera cam;
    void addGameObject(GameObject *go)
    {
        go->myscene=this;
        game_objects.push_back(go);
    }
    Scene(std::string n)
    {
        name = n;
    }
};

#endif