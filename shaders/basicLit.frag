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
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 viewPos;
uniform Material material;

#define NR_DIR_LIGHTS 4
uniform DirectionalLight dirLights[NR_DIR_LIGHTS];

#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];

vec3 CalcDirLight(DirectionalLight light, vec3 unshaded)
{
    // ambient
    vec3 ambient = light.ambient * unshaded;
  	
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
    
    return ambient + diffuse + specular;
}

vec3 CalcPointLight(PointLight light, vec3 unshaded)
{
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // ambient
    vec3 ambient = light.ambient * unshaded;
  	
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
    
    return vec3(ambient + specular + diffuse) * attenuation;
}

void main()
{
    vec3 result = vec3(0,0,0);
    
    vec4 unshaded = texture(material.texture_diffuse1,TexCoords) * material.sample_texture_diffuse1 + (1 - material.sample_texture_diffuse1) * vec4(TexCoords.x,TexCoords.y,1.0f,1.0f);

    if(unshaded.a == 0)
        discard;

    for(int i = 0; i < NR_DIR_LIGHTS; i++)
        result += CalcDirLight(dirLights[i], unshaded.rgb);
    
    for(int i = 0; i < 1; i++)
        result += CalcPointLight(pointLights[i], unshaded.rgb);
    FragColor = vec4(result, 1.0);
}
