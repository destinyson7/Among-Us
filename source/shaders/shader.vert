#version 330 core
layout (location = 0) in vec2 vertex;

out vec3 ourColor;

uniform mat4 projection;

void main()
{
    ourColor = vec3(1.0f, 0.0f, 0.0f);
    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
}
