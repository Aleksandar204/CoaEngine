#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform int sample_texture_diffuse1 = 0;
uniform sampler2D texture_diffuse1;

uniform int sample_texture_specular1 = 0;
uniform sampler2D texture_specular1;

void main()
{
    FragColor = texture(texture_diffuse1,TexCoords) * sample_texture_diffuse1 + (1 - sample_texture_diffuse1) * vec4(TexCoords.x,TexCoords.y,1.0f,1.0f);;
}