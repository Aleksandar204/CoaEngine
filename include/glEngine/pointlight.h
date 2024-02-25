#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

class PointLight : public Component
{
public:
    float constant = 1.0f,linear = 0.09f,quadratic = 0.032f;
    glm::vec3 ambient = glm::vec3(0.2f, 0.2f, 0.2f),diffuse = glm::vec3(0.5f, 0.5f, 0.5f),specular = glm::vec3(1.0f, 1.0f, 1.0f);
};

#endif