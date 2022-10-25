#version 330 core
#extension GL_ARB_separate_shader_objects : enable
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 read_colour;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 colour;
void main()
{
    gl_Position = (projection * view * model) * vec4(position.xyz, 1.0f);
    colour = read_colour;
}