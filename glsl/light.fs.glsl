#version 330 core
out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
//    float ambientStrength = 0.2;
//    vec3 ambient = ambientStrength * lightColor;
//
//    vec3 result = ambient * objectColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    vec3 result = diffuse * objectColor;
    FragColor = vec4(result, 1.0);
//    FragColor = vec4(lightColor * objectColor, 1.0);
}