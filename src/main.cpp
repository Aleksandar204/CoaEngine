#include <iostream>

#include <glEngine/engine.h>

class Spin : public Component
{
    void Update() override
    {
        game_object->modelMatrix = glm::rotate(game_object->modelMatrix, glm::radians(30.0f * (float)getDeltaTime()), glm::vec3(0.0f,1.0f,0.0f));
    }
};

class Spin2 : public Component
{
    void Update() override
    {
        game_object->rotateGlobal(glm::quat(glm::vec3(0.0f,0.0f,2.0f * getDeltaTime())));
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
        // if(glm::eulerAngles(game_object->getGlobalRotation()).x > glm::radians(80.0f))
        //     mousemovex = 0;
        // if(glm::eulerAngles(game_object->getGlobalRotation()).x < glm::radians(-80.0f))
        //     mousemovex = 0;

        float mousemovex = mouse_delta_y * sensitivity;
        float mousemovey = -mouse_delta_x * sensitivity;

        // Create quaternions for x and y rotations
        glm::quat xRotation = glm::angleAxis(glm::radians(mousemovex), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::quat yRotation = glm::angleAxis(glm::radians(mousemovey), glm::vec3(0.0f, 1.0f, 0.0f));

        // // Combine rotations
        // glm::quat totalRotation = xRotation * yRotation;

        // Apply rotation to the camera
        game_object->rotateGlobal(yRotation);
        game_object->rotateLocal(xRotation);

    }
};

int main()
{
    try
    {
        initRenderer();

        addScene("main_scene");
        setCurrentScene("main_scene");

        GameObject* ground = new GameObject(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(1.0f,1.0f,1.0f));
        ground->model = new Model("models/ground/ground.obj");
        current_scene->addGameObject(ground);

        GameObject* shrek = new GameObject(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,180.0f,0.0f),glm::vec3(1.0f,1.0f,1.0f));
        shrek->model = new Model("models/shrek/shrek.obj");
        // shrek->addComponent(new Spin());
        current_scene->addGameObject(shrek);

        GameObject* c = new GameObject(glm::vec3(5.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(1.0f,1.0f,1.0f));
        c->addComponent(new Spin2());
        c->model = new Model("models/container/untitled.obj");
        current_scene->addGameObject(c);
        shrek->addChild(c);


        current_scene->cam.modelMatrix = glm::translate(current_scene->cam.modelMatrix, glm::vec3(0.0f,0.0f,0.0f));
        current_scene->cam.addComponent(new FreeCam());
        current_scene->cam.translateLocal(glm::vec3(0.0f,5.0f,0.0f));
        // current_scene->cam.rotateLocalEuler(glm::vec3(-90.0f,0.0f,0.0f));
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