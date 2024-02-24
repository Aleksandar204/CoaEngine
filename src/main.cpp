#include <iostream>

#include <glEngine/engine.h>

class Spin : public Component
{
    void Update() override
    {
        game_object->modelMatrix = glm::rotate(game_object->modelMatrix, glm::radians(20.0f * (float)getDeltaTime()), glm::vec3(0.0f,1.0f,0.0f));
    }
};

class Move: public Component
{
    void Update() override
    {
        game_object->translateLocal(glm::vec3(getDeltaTime(),0.0f,0.0f));
    }
};

class FreeCam : public Component
{
    float speed = 5.0f, sensitivity = 0.2f;
    void Update() override
    {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            game_object->translateLocal(glm::vec3(0.0f,0.0f, getDeltaTime() * -speed));
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            game_object->translateLocal(glm::vec3(0.0f,0.0f, getDeltaTime() * speed));
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            game_object->translateLocal(glm::vec3(getDeltaTime() * -speed,0.0f,0.0f));
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            game_object->translateLocal(glm::vec3(getDeltaTime() * speed,0.0f,0.0f));
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            game_object->translateLocal(glm::vec3(0.0f,getDeltaTime()*speed, 0.0f));
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            game_object->translateLocal(glm::vec3(0.0f,-getDeltaTime()*speed, 0.0f));
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        float mousemovex = mouse_delta_y * sensitivity,mousemovey = -mouse_delta_x * sensitivity;
        // if(glm::eulerAngles(game_object->getGlobalRotation()).x > glm::radians(80.0f))
        //     mousemovex = 0;
        // if(glm::eulerAngles(game_object->getGlobalRotation()).x < glm::radians(-80.0f))
        //     mousemovex = 0;
        game_object->rotateLocalEuler(glm::vec3(mousemovex, mousemovey, 0.0f));
        //std::cout << game_object->getGlobalForward().x << " " << game_object->getGlobalForward().y << " " << game_object->getGlobalForward().z << std::endl;
    }
};

int main()
{
    try
    {
        initRenderer();

        addScene("main_scene");
        setCurrentScene("main_scene");

        GameObject* c = new GameObject(glm::vec3(0.0f,1.1f,0.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(1.0f,1.0f,1.0f));
        c->addComponent(new Spin());
        c->model = new Model("models/container/untitled.obj");
        current_scene->addGameObject(c);

        GameObject* ground = new GameObject(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(1.0f,1.0f,1.0f));
        ground->model = new Model("models/ground/ground.obj");
        current_scene->addGameObject(ground);

        GameObject* shrek = new GameObject(glm::vec3(3.0f,0.0f,3.0f),glm::vec3(45.0f,0.0f,0.0f),glm::vec3(2.0f,2.0f,2.0f));
        shrek->model = new Model("models/shrek/shrek.obj");
        shrek->addComponent(new Spin());
        current_scene->addGameObject(shrek);
        
        current_scene->cam.modelMatrix = glm::translate(current_scene->cam.modelMatrix, glm::vec3(0.0f,3.0f,6.0f));
        current_scene->cam.addComponent(new FreeCam());
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