#include <imgui/imgui.h>

#include "Te_S_La.h"
#include "Model/Model.h"
#include "Rendering/Shader.h"
#include "GLFW/glfw3.h"

int windowHeight = 800;
int windowWidth = 1200;

#define GLOBAL_UP_VECTOR glm::vec3(0, 1, 0)

float nearPlane = 0.1f;
float farPlane = 200.0f;

bool rotate = true;
bool perspective = true;

bool oToggle;
bool spaceToggle;

float angle = 0.0f;
TESLA::Model* suzanne2;
TESLA::Model* suzanne;

glm::mat4 projection = glm::perspective(glm::radians(70.0f), static_cast<float>(windowWidth)/static_cast<float>(windowHeight), nearPlane, farPlane);
glm::mat4 view = glm::lookAt( glm::vec3(1.5f, 1.0f, 1.5f), glm::vec3(0.0f),GLOBAL_UP_VECTOR);

TESLA::Model* CreateMesh(const char* fileName, const char* modelName)
{
    TESLA::Shader basicShader;
    const GLuint shaderProgram = basicShader.GetProgram();

    return new TESLA::Model(fileName, modelName, shaderProgram, view, projection);
}

void DrawGUIs()
{
    ImGui::Text("Hello world");
    ImGui::Button("Hi there");
}

void Init()
{
    TESLA::Application::Start(windowWidth, windowHeight, "Game");
    
    suzanne = CreateMesh("Suzanne.obj", "Monkey1");
    suzanne->Scale(glm::vec3(0.5, 0.5, 0.5));
    suzanne->Translate(glm::vec3(-1, 0, 0));
    
    suzanne2 = CreateMesh("Suzanne.obj", "Monkey2");
    suzanne2->Scale(glm::vec3(0.3,0.3,0.3));
    suzanne2->Translate(glm::vec3(1, 0, 0));

    TESLA::EventListener::Subscribe({[](TESLA::Event* event)
    {
        const auto castedEvent = dynamic_cast<TESLA::KeyboardButtonEvent*>(event);
        switch (castedEvent->GetKeycode())
        {
        case GLFW_KEY_O:
            if(!oToggle)
                rotate = !rotate;
            oToggle = true;
            break;
        case GLFW_KEY_SPACE:
            if(!spaceToggle)
            {
                perspective = !perspective;
            }
            spaceToggle = true;
            break;
        case GLFW_KEY_M:
            TESLA::ExitApplication();
            break;
        default:
            break;
        }
    },TESLA::EventType::ButtonPressed, TESLA::EventCategory::Keyboard});

    TESLA::EventListener::Subscribe({[](TESLA::Event* event)
    {
        const auto castedEvent = dynamic_cast<TESLA::KeyboardButtonEvent*>(event);
        switch (castedEvent->GetKeycode())
        {
        case GLFW_KEY_O:
            oToggle = false;
            break;
        case GLFW_KEY_SPACE:
            spaceToggle = false;
            break;
        default:
            break;
        }
    }, TESLA::EventType::ButtonReleased, TESLA::EventCategory::Keyboard});
}

void Render()
{
    if(rotate)
    {
        angle += 1;
        if(angle > 360) angle = 0.0f;
    }

    if(perspective)
    {
        projection = glm::perspective(glm::radians(70.0f), static_cast<float>(windowWidth)/static_cast<float>(windowHeight), nearPlane, farPlane);
    }
    else
    {
        projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, nearPlane, farPlane);
    }
    
    suzanne2->Draw(glm::vec3(1.5f, 1.0f, 1.5f));
    suzanne2->Rotate(angle, GLOBAL_UP_VECTOR);

    suzanne->Draw(glm::vec3(1.5f, 1.0f, 1.5f));
    suzanne->Rotate(angle, GLOBAL_UP_VECTOR);
}

void CleanUp()
{
    delete suzanne;
    delete suzanne2;
}