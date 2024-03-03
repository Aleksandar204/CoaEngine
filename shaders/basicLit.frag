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

    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 diffuse;
    vec3 specular;
};

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 viewPos;
uniform Material material;

#define MAX_NR_DIR_LIGHTS 32
uniform DirectionalLight dirLights[MAX_NR_DIR_LIGHTS];
uniform int nr_directional_lights;

#define MAX_NR_POINT_LIGHTS 32
uniform PointLight pointLights[MAX_NR_POINT_LIGHTS];
uniform int nr_point_lights;

uniform vec3 ambient_light;

vec3 CalcDirLight(DirectionalLight light, vec3 unshaded)
{
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * unshaded;
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * (material.sample_texture_specular1 * texture(material.texture_specular1,TexCoords).rgb + (1-material.sample_texture_specular1) * 0.1f);; 
    
    return diffuse + specular;
}

vec3 CalcPointLight(PointLight light, vec3 unshaded)
{
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * unshaded;
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * (material.sample_texture_specular1 * texture(material.texture_specular1,TexCoords).rgb + (1-material.sample_texture_specular1) * 0.1f); 
    
    return vec3(specular + diffuse) * attenuation;
}

void main()
{
    vec3 result = vec3(0,0,0);
    
    vec4 unshaded = texture(material.texture_diffuse1,TexCoords) * material.sample_texture_diffuse1 + (1 - material.sample_texture_diffuse1) * vec4(TexCoords.x,TexCoords.y,1.0f,1.0f);

    // if(unshaded.a == 0)
    //     discard;

    for(int i = 0; i < nr_point_lights; i++)
        result += CalcPointLight(pointLights[i], unshaded.rgb);

    for(int i = 0; i < nr_directional_lights; i++)
        result += CalcDirLight(dirLights[i], unshaded.rgb);
    
    result += unshaded.rgb * ambient_light;

    FragColor = vec4(result, 1.0);
}
