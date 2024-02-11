#ifndef ENGINE_H
#define ENGINE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glEngine/texture.h>
#include <glEngine/scene.h>

#include <vector>

class OpenGLEngine
{
private:
    GLFWwindow *window;

    uint32_t WINDOW_WIDTH = 1280;
    uint32_t WINDOW_HEIGHT = 720;
    const bool ENABLE_VSYNC = true;
    const bool ENABLE_RESIZING = false;

    Scene* current_scene;

    void mainLoop()
    {
        while (!glfwWindowShouldClose(window))
        {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            for (unsigned int i = 0; i < current_scene->game_objects.size(); i++)
            {
                current_scene->game_objects[i]->updateAndStart();
                current_scene->game_objects[i]->draw();
            }
            

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        
    }

    void cleanup()
    {
        glfwTerminate();
    }

    void initRenderer()
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, ENABLE_RESIZING);
        
        window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL Engine", NULL, NULL);
        if (window == NULL)
        {
                glfwTerminate();
                throw new std::runtime_error("Failed to create GLFW window");
        }

        glfwMakeContextCurrent(window);
        glfwSwapInterval(ENABLE_VSYNC);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
                throw new std::runtime_error("Failed to initialize GLAD");
        }
        glEnable(GL_DEPTH_TEST);
        glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    }
public:
    std::vector<Scene*> scenes;

    void run()
    {
        initRenderer();
        mainLoop();
        cleanup();
    }
    void addScene(std::string scene_name)
    {
        scenes.push_back(new Scene(scene_name));
    }
    void removeScene(std::string scene_name)
    {
        
    }
    Scene* getScene(std::string scene_name)
    {
        for(int i = 0; i< scenes.size(); i++)
        {
            if(scene_name == scenes[i]->name)
                return scenes[i];
        }
        return nullptr;
    }
    void setCurrentScene(std::string scene_name)
    {
        for (int i = 0; i < scenes.size(); i++)
        {
            if(scene_name == scenes[i]->name)
                current_scene = scenes[i];
        }
    }

};
#endif