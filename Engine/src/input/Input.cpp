#include "TSpch.h"
#include "Input.h"

#include "../core/Application.h"
#include "../utils/events/KeyEvents.h"
#include "GLFW/glfw3.h"

GLFWwindow* window;

std::vector<int> currKeysDown;
std::vector<int> currMouseButtonsDown;

std::vector<int> currentKeysDown;
std::vector<int> currentMouseButtonsDown;

void AddToCurrKeys(TESLA::Event* event)
{
    const auto castedEvent = dynamic_cast<TESLA::KeyboardButtonEvent*>(event);
    currKeysDown.push_back(castedEvent->GetKeycode());
}

void AddToCurrMouseButtons(TESLA::Event* event)
{
    const auto castedEvent = dynamic_cast<TESLA::MouseButtonEvent*>(event);
    currMouseButtonsDown.push_back(castedEvent->GetKeycode());
}

void TESLA::Input::Init()
{
    TESLA::Window* tsWindow = TESLA::Application::GetWindow();
    window = static_cast<GLFWwindow*>(tsWindow->GetWindow());
    
    TESLA::EventListener::Subscribe({AddToCurrKeys, TESLA::EventType::ButtonPressed, TESLA::EventCategory::Keyboard});
    TESLA::EventListener::Subscribe({AddToCurrMouseButtons, TESLA::EventType::ButtonPressed, TESLA::EventCategory::Mouse});
}

void TESLA::Input::Update()
{
    if(currentKeysDown.size() != 0)
    {
        for(int i = 0; i < currentKeysDown.size(); i++)
        {
            if(glfwGetKey(window, currentKeysDown[i]) == GLFW_RELEASE)
            {
                currentKeysDown.erase(currentKeysDown.begin() + i);
            }
        }
    }

    if(currentMouseButtonsDown.size() != 0)
    {
        for(int i = 0; i < currentMouseButtonsDown.size(); i++)
        {
            if(glfwGetMouseButton(window, currentMouseButtonsDown[i]) == GLFW_RELEASE)
            {
                currentMouseButtonsDown.erase(currentMouseButtonsDown.begin() + i);
            }
        }  
    }
}


bool TESLA::Input::GetKeyDown(int keycode)
{
    if(glfwGetKey(window, keycode) == GLFW_PRESS)
    {
        if(!(std::find(currentKeysDown.begin(), currentKeysDown.end(), keycode) != currentKeysDown.end()))
        {
            currentKeysDown.push_back(keycode);
            return true;
        }
    }
    return false;
}

bool TESLA::Input::GetKeyHeld(const int& keycode)
{
    if(glfwGetKey(window, keycode) == GLFW_PRESS)
    {
        return true;
    }
    return false;
}

bool TESLA::Input::GetKeyUp(const int& keycode)
{
    if(glfwGetKey(window, keycode) == GLFW_RELEASE)
    {
        if(const std::vector<int>::iterator&i = std::find(currKeysDown.begin(), currKeysDown.end(), keycode); i != currKeysDown.end())
        {
            currKeysDown.erase(i);
            return true;
        }
    }
    return false;
}

glm::vec2 TESLA::Input::GetMousePosition()
{
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);
    return glm::vec2(mouseX, mouseY);
}

bool TESLA::Input::GetMouseButtonDown(const int& keycode)
{
    if(glfwGetMouseButton(window, keycode) == GLFW_PRESS)
    {
        if(!(std::find(currentMouseButtonsDown.begin(), currentMouseButtonsDown.end(), keycode) != currentMouseButtonsDown.end()))
        {
            currentMouseButtonsDown.push_back(keycode);
            return true;
        }
    }
    return false;
}

bool TESLA::Input::GetMouseButtonUp(const int& keycode)
{
    if(glfwGetMouseButton(window, keycode) == GLFW_RELEASE)
    {
        if(const std::vector<int>::iterator&i = std::find(currMouseButtonsDown.begin(), currMouseButtonsDown.end(), keycode); i != currMouseButtonsDown.end())
        {
            currMouseButtonsDown.erase(i);
            return true;
        }
    }
    return false;
}

bool TESLA::Input::GetMouseButtonHeld(const int& keycode)
{
    if(glfwGetMouseButton(window, keycode) == GLFW_PRESS)
    {
        return true;
    }
    return false;
}

float TESLA::Input::GetTime()
{
    return glfwGetTime();
}

void TESLA::Input::SetInputMode(const int& mode, const int& value)
{
    glfwSetInputMode(window, mode, value);
}







