#version 330 core

struct Material {
    int sample_texture_diffuse1;
    sampler2D texture_diffuse1;
    int sample_texture_specular1;
    sampler2D texture_specular1;
    float shininess;
};

struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    vec3 unshaded = texture(material.texture_diffuse1,TexCoords).rgb * material.sample_texture_diffuse1 + (1 - material.sample_texture_diffuse1) * vec3(TexCoords.x,TexCoords.y,1.0f);

    FragColor = vec4(unshaded, 1.0);
}