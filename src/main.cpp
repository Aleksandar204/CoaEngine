#include <iostream>

#include <glEngine/engine.h>

class Spin : public Component
{
    void Start() override
    {
    }

    void Update() override
    {
        game_object->transform.rotation.y += 20.0f * getDeltaTime();
        
    }
};

class FreeCam : public Component
{
    float speed = 2.0f;
    void Update() override
    {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            game_object->transform.position.z -= speed * getDeltaTime();
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            game_object->transform.position.z += speed * getDeltaTime();
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            game_object->transform.position.x -= speed * getDeltaTime();
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            game_object->transform.position.x += speed * getDeltaTime();
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            game_object->transform.position.y += speed * getDeltaTime();
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            game_object->transform.position.y -= speed * getDeltaTime();
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }
};

int main()
{
    try
    {
        initRenderer();

        addScene("main_scene");
        setCurrentScene("main_scene");

        GameObject* c = new GameObject(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(2.1f,2.1f,2.1f));
        c->model = new Model("models/shrek/shrek.obj");
        GameObject* ground = new GameObject();
        ground->model = new Model("models/ground/ground.obj");
        c->addComponent(new Spin());
        current_scene->addGameObject(c);
        current_scene->addGameObject(ground);
        current_scene->cam.addComponent(new FreeCam());
        current_scene->cam.transform.position.z = 3.0f;
        current_scene->cam.transform.position.y = 2.0f;
        mainLoop();
        cleanup();
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}