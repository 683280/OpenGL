#version 330 core
layout (location = 0) in vec3 position; // 位置变量的属性位置值为 0
layout (location = 1) in vec3 color;    // 颜色变量的属性位置值为 1
layout (location = 2) in vec2 texCoord;    // 颜色变量的属性位置值为 1

out vec2 TexCoord;
out vec3 ourColor;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    TexCoord = vec2(1 - texCoord.x, 1.0f - texCoord.y);
    ourColor = color;
}