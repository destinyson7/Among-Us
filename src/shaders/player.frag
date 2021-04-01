#version 330 core
in vec2 TexCoords;
in vec3 FragPos;
out vec4 color;

uniform sampler2D sprite;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform float lightCutOff;
uniform int isOn;

void main()
{
    float distance = length(FragPos - lightPos);

    if(distance < lightCutOff)
    {
        if(isOn == 0)
        {
            color = vec4(lightColor * (0.8/distance) * (0.8/distance), 1.0) * texture(sprite, TexCoords);
        }

        else
        {
            color = vec4(lightColor, 1.0) * texture(sprite, TexCoords);
        }
    }

    else
    {
        color = vec4(0.00 * lightColor, 1.0) * texture(sprite, TexCoords);
    }
}
