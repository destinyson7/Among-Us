#version 330 core
layout (location = 0) in vec2 vertex;

out vec3 ourColor;
out vec3 FragPos;

uniform mat4 model;

void main()
{
    ourColor = vec3(1.0f, 0.0f, 0.0f);
    gl_Position = model * vec4(vertex.xy, 0.0, 1.0);
    FragPos = vec3(model * vec4(vertex.xy, 0.0, 1.0));
}


