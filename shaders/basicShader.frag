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

    // ambient
    vec3 ambient = light.ambient * texture(material.texture_diffuse1,TexCoords).rgb;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.texture_diffuse1,TexCoords).rgb;  
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * 1.0f;  
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}