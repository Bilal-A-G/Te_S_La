#include "Camera.h"

#include <glm/ext/matrix_transform.hpp>
#include "utils/Application.h"

glm::vec3 globalUpVector = glm::vec3(0, 1, 0);

float yaw, pitch;
bool focused;

float moveSpeed = 10;
float mouseSensitivity = 20;

float deltaTime;
float timeLastFrame;

glm::vec2 mousePosLastFrame;
glm::vec2 mouseDelta;

void CursorCallback(GLFWwindow* _, double mousex, double mousey)
{
    if(focused)
    {
        mousePosLastFrame = glm::vec2(mousex, mousey);
        focused = false;
    }
    mouseDelta = glm::vec2(mousex, mousey) - mousePosLastFrame;

    yaw += mouseDelta.x * mouseSensitivity * deltaTime;
    pitch -= mouseDelta.y * mouseSensitivity * deltaTime;

    pitch = glm::clamp(pitch, -89.0f, 89.0f);
        
    mousePosLastFrame = glm::vec2(mousex, mousey);
}

void MouseCallback(GLFWwindow* _, int button, int action, int mods)
{
    if(button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        if(action == GLFW_PRESS)
        {
            TESLA::Application::SetInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            TESLA::Application::SetMouseCursorCallback(CursorCallback);
        }
        else if(action == GLFW_RELEASE)
        {
            TESLA::Application::SetInputMode(GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            TESLA::Application::ReturnCursor();
            focused = true;
        }
    }
}

glm::mat4 Camera::CalculateView()
{
    deltaTime = TESLA::Application::GetTime() - timeLastFrame;
    
    TESLA::Application::SetMouseButtonCallback(MouseCallback);
    
    cameraDirection.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraDirection.y = sin(glm::radians(pitch));
    cameraDirection.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    cameraDirection = glm::normalize(cameraDirection);
    
    const glm::vec3 cameraRight = glm::normalize(glm::cross(globalUpVector, cameraDirection));
    const glm::vec3 cameraUp = glm::normalize(glm::cross(cameraDirection, cameraRight));

    const float cameraSpeed = moveSpeed * deltaTime;

    if(TESLA::Application::ImGUIWantsKeyboard())
    {
        focused = true;
        return glm::mat4(1);
    }
    
    if(TESLA::Application::GetKey(GLFW_KEY_W) == GLFW_PRESS)
        cameraPosition += cameraDirection * cameraSpeed;
    if(TESLA::Application::GetKey(GLFW_KEY_S) == GLFW_PRESS)
        cameraPosition -= cameraDirection * cameraSpeed;
    
    if(TESLA::Application::GetKey(GLFW_KEY_A) == GLFW_PRESS)
        cameraPosition += cameraRight * cameraSpeed;
    if(TESLA::Application::GetKey(GLFW_KEY_D) == GLFW_PRESS)
        cameraPosition -= cameraRight * cameraSpeed;
    
    if(TESLA::Application::GetKey(GLFW_KEY_SPACE) == GLFW_PRESS)
        cameraPosition += cameraUp * cameraSpeed;
    if(TESLA::Application::GetKey(GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        cameraPosition -= cameraUp * cameraSpeed;

    timeLastFrame = TESLA::Application::GetTime();
    
    return glm::lookAt(cameraPosition, cameraPosition + cameraDirection, globalUpVector);
}

