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
#include <glEngine/pointlight.h>
#include <glEngine/directionallight.h>

#include <vector>
#include <cmath>

GLFWwindow *window;

std::vector<Scene*> scenes;
Scene* current_scene;
Shader* skybox_shader;
uint32_t WINDOW_WIDTH = 1280;
uint32_t WINDOW_HEIGHT = 720;
const bool ENABLE_VSYNC = true;
const bool ENABLE_RESIZING = false;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

double lastX = 0.0f, lastY = 0.0f;
bool firstMouse = true;

double mouse_delta_x, mouse_delta_y;
bool mouse_moved = false;
double xp,yp;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    xp = xpos;
    yp = ypos;
    if(firstMouse)
    {
        lastX = xp;
        lastY = yp;
        firstMouse = false;
    }
}

unsigned int skyboxVAO;
unsigned int skyboxVBO;
float skyboxVertices[108] = {
    // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f,  1.0f
};

std::vector<DirectionalLight*> dirLights;
std::vector<PointLight*> pointLights;

std::vector<DirectionalLight*> getDirectionalLights()
{
    std::vector<DirectionalLight*> temp;
    for (int i = 0; i < current_scene->game_objects.size(); i++)
    {
        for (int j = 0; j < current_scene->game_objects[i]->components.size(); j++)
        {
            if(DirectionalLight* p = dynamic_cast<DirectionalLight*>(current_scene->game_objects[i]->components[j]))
                temp.push_back(p);
        }
        
    }
    return temp;
}

std::vector<PointLight*> getPointLights()
{
    std::vector<PointLight*> temp;
    for (int i = 0; i < current_scene->game_objects.size(); i++)
    {
        for (int j = 0; j < current_scene->game_objects[i]->components.size(); j++)
        {
            if(PointLight* p = dynamic_cast<PointLight*>(current_scene->game_objects[i]->components[j]))
                temp.push_back(p);
        }
        
    }
    return temp;
}

void render(GameObject* go)
{
    Model* mod = go->model;
    for (unsigned int i = 0; i < mod->meshes.size(); i++)
    {
        mod->meshes[i].shader.use();


        mod->meshes[i].shader.setMat4("model", go->getGlobalModelMatrix());
        mod->meshes[i].shader.setMat4("view", current_scene->cam.getViewMatrix());
        mod->meshes[i].shader.setMat4("projection", glm::perspective(glm::radians(current_scene->cam.fov), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f));

        unsigned int j,cnt,k;
        for (j = 0, cnt = 1; j < mod->meshes[i].diffuseMaps.size(); j++)
        {
            glActiveTexture(GL_TEXTURE0 + j);
            mod->meshes[i].shader.setInt("material.texture_diffuse" + std::to_string(cnt),j);
            mod->meshes[i].shader.setInt("material.sample_texture_diffuse" + std::to_string(cnt++),1);
            mod->meshes[i].diffuseMaps[j]->use();
        }
        
        for (cnt = 1; j < mod->meshes[i].specularMaps.size() + mod->meshes[i].diffuseMaps.size(); j++)
        {
            glActiveTexture(GL_TEXTURE0 + j);
            mod->meshes[i].shader.setInt("material.texture_specular" + std::to_string(cnt),j);
            mod->meshes[i].shader.setInt("material.sample_texture_specular" + std::to_string(cnt++),1);
            
            mod->meshes[i].specularMaps[j - mod->meshes[i].diffuseMaps.size()]->use();
        }

        for (int dirL = 0; dirL < dirLights.size(); dirL++)
        {

            mod->meshes[i].shader.setVec3("dirLights[" + std::to_string(dirL) + "].direction", dirLights[dirL]->direction);

            mod->meshes[i].shader.setVec3("dirLights[" + std::to_string(dirL) + "].diffuse", dirLights[dirL]->diffuse);
            mod->meshes[i].shader.setVec3("dirLights[" + std::to_string(dirL) + "].specular", dirLights[dirL]->specular);
        }
        for (int pointL = 0; pointL < pointLights.size(); pointL++)
        {
            mod->meshes[i].shader.setVec3("pointLights[" + std::to_string(pointL) + "].position", pointLights[pointL]->game_object->getGlobalPosition());

            mod->meshes[i].shader.setFloat("pointLights[" + std::to_string(pointL) + "].constant", pointLights[pointL]->constant);
            mod->meshes[i].shader.setFloat("pointLights[" + std::to_string(pointL) + "].linear", pointLights[pointL]->linear);
            mod->meshes[i].shader.setFloat("pointLights[" + std::to_string(pointL) + "].quadratic", pointLights[pointL]->quadratic);

            mod->meshes[i].shader.setVec3("pointLights[" + std::to_string(pointL) + "].diffuse", pointLights[pointL]->diffuse);
            mod->meshes[i].shader.setVec3("pointLights[" + std::to_string(pointL) + "].specular", pointLights[pointL]->specular);
        }

        mod->meshes[i].shader.setInt("nr_point_lights", pointLights.size());
        mod->meshes[i].shader.setInt("nr_directional_lights", dirLights.size());

        mod->meshes[i].shader.setVec3("ambient_light", current_scene->skybox.getAmbientLight());
        

        mod->meshes[i].shader.setFloat("material.shininess", 32.0f);
        mod->meshes[i].shader.setVec3("viewPos", current_scene->cam.getGlobalPosition());

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
    glfwWindowHint(GLFW_SAMPLES, 4);

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL Engine", NULL, NULL);
    if (window == NULL)
    {
            glfwTerminate();
            throw new std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(ENABLE_VSYNC);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
            throw new std::runtime_error("Failed to initialize GLAD");
    }
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    // glEnable(GL_CULL_FACE);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    skybox_shader = new Shader("shaders/skybox.vert", "shaders/skybox.frag");
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

void renderSkybox()
{
    skybox_shader->use();
    skybox_shader->setMat4("view", glm::mat4(glm::mat3(current_scene->cam.getViewMatrix())));
    skybox_shader->setMat4("projection", glm::perspective(glm::radians(current_scene->cam.fov), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f));

    glDepthFunc(GL_LEQUAL);
    
    glBindVertexArray(skyboxVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, current_scene->skybox.getID());
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    
    glDepthFunc(GL_LESS);
}

void mainLoop()
{
    while (!glfwWindowShouldClose(window))
    {
        double currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        setDeltaTime(deltaTime);
        
        mouse_delta_x = xp - lastX;
        mouse_delta_y = lastY - yp;
        lastX = xp;
        lastY = yp;
        mouse_moved = true;

        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        std::vector<GameObject*> gos = current_scene->game_objects;
        // current_scene->cam.transform.position.z += 0.5f * getDeltaTime();
        // current_scene->cam.rotation.y += getDeltaTime() * 10.0f;
        for (unsigned int i = 0; i < current_scene->game_objects.size(); i++)
        {
            current_scene->game_objects[i]->getAllChildren(&gos);
        }
        std::vector<DirectionalLight*> temp;
        std::vector<PointLight*> temp2;
        for (unsigned int i = 0; i < gos.size(); i++)
        {
            gos[i]->updateAndStart();

            for (int j = 0; j < gos[i]->components.size(); j++)
            {
                if(DirectionalLight* p = dynamic_cast<DirectionalLight*>(gos[i]->components[j]))
                    temp.push_back(p);
            }

            for (int j = 0; j < gos[i]->components.size(); j++)
            {
                if(PointLight* p = dynamic_cast<PointLight*>(gos[i]->components[j]))
                    temp2.push_back(p);
            }
        }

        dirLights = temp;
        pointLights = temp2;

        for (unsigned int i = 0; i < gos.size(); i++)
        {
            if(gos[i]->model != nullptr)
                render(gos[i]);
        }

        renderSkybox();


        if(mouse_moved)
        {
            mouse_moved = false;
            mouse_delta_x = 0;
            mouse_delta_y = 0;
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

#endif