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
#include <glEngine/time.h>
#include <glEngine/gameobject.h>

#include <vector>
#include <cmath>

class OpenGLEngine
{
private:
    GLFWwindow *window;

    uint32_t WINDOW_WIDTH = 1280;
    uint32_t WINDOW_HEIGHT = 720;
    const bool ENABLE_VSYNC = true;
    const bool ENABLE_RESIZING = false;

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;


    Scene* current_scene;
    
    void mainLoop()
    {
        while (!glfwWindowShouldClose(window))
        {
            double currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
            setDeltaTime(deltaTime);


            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            std::vector<GameObject*> gos = current_scene->game_objects;
            // current_scene->cam.transform.position.z += 0.5f * getDeltaTime();
            // current_scene->cam.rotation.y += getDeltaTime() * 10.0f;
            for (unsigned int i = 0; i < current_scene->game_objects.size(); i++)
            {
                current_scene->game_objects[i]->getAllChildren(&gos);
            }
            
            

            for (unsigned int i = 0; i < gos.size(); i++)
            {
                gos[i]->updateAndStart();
                
                if(gos[i]->model != nullptr)
                    render(gos[i]);
            }
            

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        
    }

    void render(GameObject* go)
    {
        Model* mod = go->model;
        for (unsigned int i = 0; i < mod->meshes.size(); i++)
        {
            mod->meshes[i].shader.use();

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model,go->getGlobalPosition());
            model *= glm::toMat4(glm::quat(glm::radians(go->getGlobalRotation())));
            glm::mat4 view          = current_scene->cam.getViewMatrix();
            glm::mat4 projection    = glm::perspective(glm::radians(current_scene->cam.fov), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
            unsigned int modelLoc = glGetUniformLocation(mod->meshes[i].shader.shader_id, "model");
            unsigned int viewLoc  = glGetUniformLocation(mod->meshes[i].shader.shader_id, "view");
            unsigned int projectionLoc  = glGetUniformLocation(mod->meshes[i].shader.shader_id, "projection");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);

            glActiveTexture(GL_TEXTURE0);

            glBindVertexArray(mod->meshes[i].getVAO());
            glDrawElements(GL_TRIANGLES, mod->meshes[i].indices.size(), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }
    }

    void cleanup()
    {
        glfwTerminate();
    }

    void initRenderer()
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

    OpenGLEngine()
    {
        initRenderer();
    }

    void run()
    {
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