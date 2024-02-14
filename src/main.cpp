#include <iostream>

#include <glEngine/engine.h>
#include <glEngine/scene.h>
#include <glEngine/gameobject.h>
#include <glEngine/component.h>

#include <glEngine/time.h>

class Movecube : public Component
{
    void Start() override
    {
        std::cout << "I'm a rotating cube!" << std::endl;
    }

    void Update() override
    {
        game_object->transform.rotation.y += 10.0f * getDeltaTime();
    }
};
class Movecube2 : public Component
{
    void Start() override
    {
        std::cout << "I'm a child cube!" << std::endl;
    }

    void Update() override
    {
        game_object->transform.rotation.z += 20.0f * getDeltaTime();
    }
};

int main()
{
    OpenGLEngine game;

    game.addScene("main_scene");
    GameObject* c = new GameObject(glm::vec3(-0.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,0.0f));
    GameObject* c2 = new GameObject(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,0.0f));
    // c->addComponent(new Movecube());
    // c2->addComponent(new Movecube2());
    // c->addChild(c2);
    game.getScene("main_scene")->addGameObject(c);
    // game.getScene("main_scene")->addGameObject(c2);
    game.setCurrentScene("main_scene");
    

    try
    {
        game.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}