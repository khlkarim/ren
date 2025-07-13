#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

uniform float time;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    TexCoords = aTexCoords;    
    gl_Position = projection * view * model * vec4(aPos.x + aNormal.x * sin(time) * sin(time), aPos.y + aNormal.y * cos(time)* sin(time), aPos.z, 1.0);
}