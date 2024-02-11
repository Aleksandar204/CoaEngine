#include <iostream>

#include <glEngine/engine.h>
#include <glEngine/scene.h>
#include <glEngine/gameobject.h>

class Cube : public GameObject
{
    void Start() override
    {
        std::cout << "Im a cube!" << std::endl;
        position.z = -2.0f;
        
    }
    void Update() override
    {
        std::cout << rotation.x << std::endl;
        // position.z -= 0.01f;
        rotation.x += 1.0f;

    }
};

int main()
{
    OpenGLEngine game;

    game.addScene("main_scene");
    GameObject* c = new Cube();
    game.getScene("main_scene")->addGameObject(c);
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