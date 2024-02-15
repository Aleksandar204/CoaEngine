#include <iostream>

#include <glEngine/engine.h>

class Movecube : public Component
{
    void Start() override
    {
        std::cout << "I'm a rotating cube!" << std::endl;
    }

    void Update() override
    {
        game_object->transform.rotation.y += 20.0f * getDeltaTime();
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
    try
    {
        OpenGLEngine game;

        game.addScene("main_scene");
        GameObject* c = new GameObject(glm::vec3(-0.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.01f,0.01f,0.01f));
        // GameObject* c2 = new GameObject(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,0.0f));
        c->model = new Model("/home/coa/Projects/Personal/OpenGLBetter/models/Survival_BackPack_2/Survival_BackPack_2.fbx");
        c->addComponent(new Movecube());
        // c2->addComponent(new Movecube2());
        // c->addChild(c2);
        game.getScene("main_scene")->addGameObject(c);
        game.getScene("main_scene")->cam.transform.position.z +=6.0f;
        // game.getScene("main_scene")->addGameObject(c2);
        game.setCurrentScene("main_scene");
        game.run();
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}