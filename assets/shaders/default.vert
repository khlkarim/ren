#version 330 core
layout (location = 0) in vec3 aPosition; 
layout (location = 1) in vec3 aNormal; 
layout (location = 2) in vec2 aTexCoords; 

out vec3 Normal;
out vec2 TexCoords;

void main()
{
    gl_Position = vec4(aPosition/2.5, 1.0);
    Normal = aNormal;
    TexCoords = aTexCoords;
}