#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec3 lightPos;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    
    vec3 lightColor = vec3(1.0f, 0.5f, 0.0f);
    // Tells you the % of each channel the object reflects
    vec3 objectColor = vec3(1.0f, 0.5f, 0.0f);

    vec3 diffuse = diff * lightColor;

    // Tells you the % of each channel (from the source) is ambient
    float ambientStrength = 0.1f;

    // Calculates the quantity of ambient light an each channel
    vec3 ambient = ambientStrength * lightColor;

    // Calculates how much of that ambient light the object reflects
    vec3 result = (ambient + diffuse) * objectColor;

    FragColor = vec4(result, 1.0f);
}