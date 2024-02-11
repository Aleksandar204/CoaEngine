#include <iostream>

#include <glEngine/engine.h>
#include <glEngine/scene.h>
#include <glEngine/gameobject.h>

class Cube : public GameObject
{
    void Start() override
    {
        std::cout << "Im a cube!" << std::endl;
    }
    void Update() override
    {
        // std::cout << position.x << std::endl;
    }
};

int main()
{
    OpenGLEngine game;

    game.addScene("main_scene");
    game.getScene("main_scene")->addGameObject(new Cube());
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