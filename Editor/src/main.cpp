#include "Te_S_La.h"
#include "Camera.h"
#include "input/Input.h"
#include "utils/events/KeyEvents.h"
#include "utils/physics/Physics.h"

int windowHeight = 800;
int windowWidth = 1200;

float nearPlane = 0.1f;
float farPlane = 200.0f;

char sceneTextBuffer[20] = "";
TESLA::Model* activeModel;

glm::mat4 projection = glm::perspective(glm::radians(70.0f), static_cast<float>(windowWidth)/static_cast<float>(windowHeight), nearPlane, farPlane);
glm::mat4 view = glm::mat4(0);

TESLA::Model* ImportModel(const char* fileName, const char* modelName)
{
    TESLA::Shader basicShader;
    GLuint shaderProgram = basicShader.GetProgram();

    return new TESLA::Model{fileName, modelName, shaderProgram, view, projection};
}

std::vector<TESLA::Model*> sceneObjects;

void DrawGUIs()
{
    {
        TESLA::Application::BeginGUI("Create");
        if(TESLA::Application::CreateButton("Create Object"))
        {
            sceneObjects.push_back(ImportModel("cube.obj", "Joe Mama"));
        }
        TESLA::Application::EndGUI();
    }
    {
        TESLA::Application::BeginGUI("Export");
        TESLA::Application::CreateButton("Export Scene To File");
        TESLA::Application::CreateInputText("Scene name", sceneTextBuffer, sizeof(sceneTextBuffer), ImGuiInputTextFlags_AutoSelectAll);
        TESLA::Application::EndGUI();
    }
}

void HandleKeyboardEvents(TESLA::Event* event)
{
    switch (const auto castedEvent = dynamic_cast<TESLA::KeyboardButtonEvent*>(event); castedEvent->GetKeycode())
    {
    case GLFW_KEY_ESCAPE:
        TESLA::ExitApplication();
        [[fallthrough]];
    default:
        break;
    }
}

void HandleMouseEvents(TESLA::Event* event)
{
    TESLA_PHYSICS::RaycastResult result{};
    
    switch (const auto castedEvent = dynamic_cast<TESLA::MouseButtonEvent*>(event); castedEvent->GetKeycode())
    {
    case GLFW_MOUSE_BUTTON_LEFT:
        if (TESLA_PHYSICS::Raycaster::Raycast(Camera::cameraPosition, Camera::cameraDirection, 1000, 1000, sceneObjects, result))
        {
            TS_LOG_MESSAGE(TESLA_LOGGER::DEBUG, "Hit {0}", result.hitObject->name);
            activeModel = result.hitObject;
        }
        else
        {   
            activeModel = nullptr;
        }
        break;
    default:
        break;
    }
}

void Init()
{
    TESLA::Application::Start(windowWidth, windowHeight, "Editor");
    
    sceneObjects.push_back(ImportModel("cube.obj", "Cube 1"));
    sceneObjects[0]->Translate(glm::vec3(5, 0, 0));

    sceneObjects.push_back(ImportModel("cube.obj", "Cube 2"));
    sceneObjects[1] ->Translate(glm::vec3(2, 2, 2));

    TESLA::EventListener::Subscribe({HandleKeyboardEvents, TESLA::EventType::ButtonPressed, TESLA::EventCategory::Keyboard});
    TESLA::EventListener::Subscribe({HandleMouseEvents, TESLA::EventType::ButtonPressed, TESLA::EventCategory::Mouse});
    
    Camera::Init();
}

void Render()
{
    for (TESLA::Model* model : sceneObjects)
        model->Draw();
        
    glm::mat4 newView = Camera::CalculateView();
    if(newView != glm::mat4(1))
    {
        view = newView;
    }
}

void CleanUp()
{
    TS_LOG_MESSAGE(TESLA_LOGGER::DEBUG, "Application ended");
    sceneObjects.clear();
}