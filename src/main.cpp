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
    void Update(float deltaTime) override
    {
        // std::cout << rotation.x << std::endl;
        // position.z -= 0.01f;
        rotation.x += 10.0f * deltaTime;

    }
public:
    Cube(glm::vec3 pos, glm::vec3 rot, glm::vec3 si)
    {
        position = pos;
        rotation = rot;
        size = si;
    }
};

int main()
{
    OpenGLEngine game;

    game.addScene("main_scene");
    GameObject* c = new Cube(glm::vec3(1.5f,0.0f,-2.0f),glm::vec3(0.0f,45.0f,0.0f),glm::vec3(0.0f,0.0f,0.0f));
    GameObject* c2 = new Cube(glm::vec3(0.0f,0.0f,-2.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,0.0f));
    game.getScene("main_scene")->addGameObject(c);
    game.getScene("main_scene")->addGameObject(c2);
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