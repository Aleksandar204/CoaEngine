#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

class DirectionalLight : public Component
{
public:
    glm::vec3 diffuse = glm::vec3(0.5f, 0.5f, 0.5f),specular = glm::vec3(1.0f, 1.0f, 1.0f), direction = glm::vec3(0.5f, -0.7f, 0.3f);
};

#endif