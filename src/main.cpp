#include <iostream>

#include <glEngine/engine.h>

class Spin : public Component
{
    void Update() override
    {
        game_object->transform.rotation.y += 20.0f * getDeltaTime();
    }
};

class Move: public Component
{
    void Update() override
    {
        game_object->transform.position.y -= 0.3f * getDeltaTime();
    }
};

class FreeCam : public Component
{
    float speed = 5.0f, sensitivity = 0.2f;
    void Update() override
    {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            game_object->transform.position += glm::normalize(glm::vec3(game_object->transform.forward().x,0.0f,game_object->transform.forward().z)) * glm::vec3(getDeltaTime()) * glm::vec3(speed);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            game_object->transform.position += glm::normalize(glm::vec3(game_object->transform.forward().x,0.0f,game_object->transform.forward().z)) * glm::vec3(getDeltaTime()) * glm::vec3(-speed);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            game_object->transform.position += game_object->transform.right() * glm::vec3(getDeltaTime()) * glm::vec3(-speed);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            game_object->transform.position += game_object->transform.right() * glm::vec3(getDeltaTime()) * glm::vec3(speed);
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            game_object->transform.position.y += speed * getDeltaTime();
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            game_object->transform.position.y -= speed * getDeltaTime();
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        game_object->transform.rotation.y -= mouse_delta_x * sensitivity;
        game_object->transform.rotation.x += mouse_delta_y * sensitivity;

        if(game_object->transform.rotation.x > 80.0f)
            game_object->transform.rotation.x = 80.0f;
        if(game_object->transform.rotation.x < -80.0f)
            game_object->transform.rotation.x = -80.0f;
    }
};

int main()
{
    try
    {
        initRenderer();

        addScene("main_scene");
        setCurrentScene("main_scene");

        GameObject* c = new GameObject(glm::vec3(2.0f,10.0f,0.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.5f,0.5f,0.5f));
        GameObject* box = new GameObject(glm::vec3(0.0f,-9.0f,-1.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(10.0f,10.0f,10.0f));
        box->model = new Model("models/container/untitled.obj");
        c->model = new Model("models/container/untitled.obj");
        GameObject* ground = new GameObject();
        ground->model = new Model("models/ground/ground.obj");
        box->addComponent(new Move());
        // c->addComponent(new Move());
        current_scene->addGameObject(c);
        current_scene->addGameObject(box);
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