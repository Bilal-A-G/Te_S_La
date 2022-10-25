#include "Camera.h"
#include <glm/ext/matrix_transform.hpp>
#include "Core/Application.h"
#include "Input/Input.h"

#include "GLFW/glfw3.h"

glm::vec3 globalUpVector = glm::vec3(0, 1, 0);

float yaw, pitch;
bool focused;

float moveSpeed = 10;
float mouseSensitivity = 20;

float deltaTime;
float timeLastFrame;

glm::vec2 mousePosLastFrame;
glm::vec2 mouseDelta;

void CursorCallback(TESLA::Event* event)
{
    const auto castedEvent = dynamic_cast<TESLA::MouseMovedEvent*>(event);
    
    if(focused)
    {
        mousePosLastFrame = glm::vec2(castedEvent->GetMouseX(), castedEvent->GetMouseY());
        focused = false;
    }
    mouseDelta = glm::vec2(castedEvent->GetMouseX(), castedEvent->GetMouseY()) - mousePosLastFrame;

    yaw += mouseDelta.x * mouseSensitivity * deltaTime;
    pitch -= mouseDelta.y * mouseSensitivity * deltaTime;

    pitch = glm::clamp(pitch, -89.0f, 89.0f);
        
    mousePosLastFrame = glm::vec2(castedEvent->GetMouseX(), castedEvent->GetMouseY());
}

void Camera::Init()
{
    focused = true;
}

glm::mat4 Camera::CalculateView()
{
    deltaTime = TESLA::Input::GetTime() - timeLastFrame;

    cameraDirection.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraDirection.y = sin(glm::radians(pitch));
    cameraDirection.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    cameraDirection = glm::normalize(cameraDirection);

    const glm::vec3 cameraRight = glm::normalize(glm::cross(globalUpVector, cameraDirection));
    const glm::vec3 cameraUp = glm::normalize(glm::cross(cameraDirection, cameraRight));
    const float cameraSpeed = moveSpeed * deltaTime;

    if(TESLA::Input::GetMouseButtonUp(GLFW_MOUSE_BUTTON_RIGHT))
    {
        TESLA::EventListener::UnSubscribe(CursorCallback);
        TESLA::Input::SetInputMode(GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        focused = true;
    }
    else if(TESLA::Input::GetMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT))
    {
        TESLA::EventListener::Subscribe({CursorCallback, TESLA::EventType::MouseMoved, TESLA::EventCategory::Mouse});
        TESLA::Input::SetInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    if(TESLA::Input::GetKeyHeld(GLFW_KEY_W))
    {
        cameraPosition += cameraDirection * cameraSpeed;
    }
    if(TESLA::Input::GetKeyHeld(GLFW_KEY_S))
    {
        cameraPosition -= cameraDirection * cameraSpeed;
    }
    if(TESLA::Input::GetKeyHeld(GLFW_KEY_A))
    {
        cameraPosition += cameraRight * cameraSpeed;
    }
    if(TESLA::Input::GetKeyHeld(GLFW_KEY_D))
    {
        cameraPosition -= cameraRight * cameraSpeed;
    }
    if(TESLA::Input::GetKeyHeld(GLFW_KEY_SPACE))
    {
        cameraPosition += cameraUp * cameraSpeed;
    }
    if(TESLA::Input::GetKeyHeld(GLFW_KEY_LEFT_CONTROL))
    {
        cameraPosition -= cameraUp * cameraSpeed;
    }

    timeLastFrame = TESLA::Input::GetTime();
    
    return glm::lookAt(cameraPosition, cameraPosition + cameraDirection, globalUpVector);
}

