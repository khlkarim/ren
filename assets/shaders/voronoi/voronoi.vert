#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 Color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 vertexPositions[100];
uniform vec3 vertexColors[100];

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);

    float minDist = distance(aPos, vertexPositions[0]);
    Color = vertexColors[0];

    if(minDist < 0.03f)
    {
        Color = vec3(1.0f);
    }

    for(int i = 1; i < 15; i++) 
    {
        float dist = distance(aPos, vertexPositions[i]);
        if(dist < minDist)
        {
            minDist = dist;

            if(dist < 0.03f)
            {
                Color = vec3(1.0f);
            }
            else 
            {
                Color = vertexColors[i];
            }
        }
    }    
}