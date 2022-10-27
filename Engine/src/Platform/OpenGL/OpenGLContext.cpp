#include "TSpch.h"
#include "glad/glad.h"
#include "OpenGLContext.h"

void TESLA::OpenGLContext::Init()
{
    glfwMakeContextCurrent(m_window);
    const bool gladLoaded = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

    TS_LOG_ASSERTION(gladLoaded, TESLA_LOGGER::ERR, "Failed to load GLAD");
    TS_LOG_MESSAGE(TESLA_LOGGER::INFO, "Successfully loaded GLAD");

    TS_LOG_MESSAGE(TESLA_LOGGER::INFO, "OpenGL Renderer {0}", glGetString(GL_RENDERER));
}

void TESLA::OpenGLContext::ResizeBuffer(const int width, const int height)
{
    glViewport(0, 0, width, height);
}

void TESLA::OpenGLContext::SwapBuffers()
{
    glfwSwapBuffers(m_window);
}



