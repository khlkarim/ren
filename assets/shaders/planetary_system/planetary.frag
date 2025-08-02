#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    sampler2D texture_normal2;
};

uniform Material material;

void main()
{
    vec4 color = texture(material.texture_diffuse1, TexCoords);
    FragColor = color;
}