#version 330 core

in vec3 ourColor;
in vec3 FragPos;
out vec4 FragColor;

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
            FragColor = vec4(lightColor * (0.8/distance) * (0.8/distance) * ourColor, 1.0);
        }

        else
        {
            FragColor = vec4(lightColor * ourColor, 1.0);
        }
    }

    else
    {
        FragColor = vec4(0.00 * lightColor * ourColor, 1.0);
    }
}
