#version 330 core
in vec3 colour;
out vec4 frag_colour;
void main()
{
    frag_colour = vec4(colour.xyz * 0.5 + 0.5, 0.0f);
}