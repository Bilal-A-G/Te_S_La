#include "TSpch.h"
#include "glad/glad.h"
#include "OpenGLContext.h"

void TESLA::OpenGLContext::Init()
{
    glfwMakeContextCurrent(m_window);
    const bool gladLoaded = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

    TS_LOG_ASSERTION(gladLoaded, TESLA_LOGGER::ERR, "Failed to load GLAD");
    TS_LOG_MESSAGE(TESLA_LOGGER::INFO, "Successfully loaded GLAD");
}

void TESLA::OpenGLContext::ResizeBuffer(const int width, const int height)
{
    glViewport(0, 0, width, height);
}

void TESLA::OpenGLContext::RenderLoop()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void TESLA::OpenGLContext::SwapBuffers()
{
    glfwSwapBuffers(m_window);
}


