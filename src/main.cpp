#include <iostream>

#include <glEngine/engine.h>

class Movecube : public Component
{
    void Start() override
    {
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
        game.setCurrentScene("main_scene");

        GameObject* c = new GameObject(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(1.1f,1.1f,1.1f));
        c->model = new Model("models/shrek/shrek.obj");
        game.current_scene->addGameObject(c);
        game.current_scene->cam.transform.position.z = 3.0f;
        game.current_scene->cam.transform.position.y = 2.0f;
        game.run();
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}