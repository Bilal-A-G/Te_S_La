#include "CameraMovement.h"

#include <glm/ext/matrix_transform.hpp>
#include <imgui/imgui_impl_glfw.h>
#include "utils/Logger.h"

glm::vec3 globalUpVector = glm::vec3(0, 1, 0);
glm::vec3 cameraPosition = glm::vec3(1.5f, 1.0f, 1.5f);
glm::vec3 cameraTarget = glm::vec3(0);

float yaw, pitch;
bool focused;

float moveSpeed = 10;
float mouseSensitivity = 20;

float deltaTime;
float timeLastFrame;

glm::vec2 mousePosLastFrame;
glm::vec2 mouseDelta;

void CursorCallback(GLFWwindow* window, double mousex, double mousey)
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

void MouseCallback(GLFWwindow* window, int button, int action, int mods)
{
    if(button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        if(action == GLFW_PRESS)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            glfwSetCursorPosCallback(window, CursorCallback);
        }
        else if(action == GLFW_RELEASE)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            glfwSetCursorPosCallback(window, ImGui_ImplGlfw_CursorPosCallback);
            focused = true;
        }
    }
}

glm::mat4 CameraMovement::Look(GLFWwindow* window)
{
    deltaTime = glfwGetTime() - timeLastFrame;

    glfwSetMouseButtonCallback(window, MouseCallback);
    
    glm::vec3 cameraDirection;
    cameraDirection.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraDirection.y = sin(glm::radians(pitch));
    cameraDirection.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    cameraDirection = glm::normalize(cameraDirection);
    
    const glm::vec3 cameraRight = glm::normalize(glm::cross(globalUpVector, cameraDirection));
    const glm::vec3 cameraUp = glm::normalize(glm::cross(cameraDirection, cameraRight));

    const float cameraSpeed = moveSpeed * deltaTime;
    
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPosition += cameraDirection * cameraSpeed;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPosition -= cameraDirection * cameraSpeed;
    
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPosition += cameraRight * cameraSpeed;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPosition -= cameraRight * cameraSpeed;
    
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cameraPosition -= cameraUp * cameraSpeed;
    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        cameraPosition += cameraUp * cameraSpeed;

    timeLastFrame = glfwGetTime();
    
    return glm::lookAt(cameraPosition, cameraPosition + cameraDirection, globalUpVector);
}

