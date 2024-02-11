#version 330 core
out vec4 FragColor;

in vec2 bingus;

void main()
{
    FragColor = vec4(bingus.x,bingus.y,1.0f,1.0f);
}