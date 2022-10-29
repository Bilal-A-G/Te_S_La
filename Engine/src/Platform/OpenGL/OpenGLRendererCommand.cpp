#include "TSpch.h"
#include "OpenGLRendererCommand.h"

#include <GL/gl.h>

void TESLA::OpenGLRendererCommand::Clear()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void TESLA::OpenGLRendererCommand::SetClearColour(glm::vec4 colour)
{
    glClearColor(colour.x, colour.y, colour.z, colour.w);
}


