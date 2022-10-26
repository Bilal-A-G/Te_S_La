#version 330 core
#extension GL_ARB_separate_shader_objects : enable
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 colour;
void main()
{
    vec3 objectColour = vec3(0.5f, 0.2f, 0.1f);
    vec3 lightColour = vec3(1.0f, 1.0f, 1.0f);
    
    float ambientStrength = 0.3f;
    vec3 ambientLight = ambientStrength * lightColour;
    
    vec3 totalLight = objectColour * ambientLight;
    
    gl_Position = (projection * view * model) * vec4(position.xyz, 1.0f);
    colour = totalLight;
}