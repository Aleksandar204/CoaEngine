#version 330 core

struct Material {
    int sample_texture_diffuse1;
    sampler2D texture_diffuse1;
    int sample_texture_specular1;
    sampler2D texture_specular1;
    float shininess;
};

struct DirectionalLight
{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 viewPos;
uniform Material material;

#define NR_DIR_LIGHTS 4
uniform DirectionalLight dirLights[NR_DIR_LIGHTS];

#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];

void main()
{
    vec3 unshaded = texture(material.texture_diffuse1,TexCoords).rgb * material.sample_texture_diffuse1 + (1 - material.sample_texture_diffuse1) * vec3(1.0f);
    FragColor = vec4(unshaded, 1.0);
}