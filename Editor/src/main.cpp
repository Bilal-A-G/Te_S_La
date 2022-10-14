#include "Te_S_La.h"
#include "Camera.h"
#include "utils/Physics.h"

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

int SetActiveObjectName(ImGuiInputTextCallbackData* data)
{
    TS_LOG_MESSAGE(TESLA_LOGGER::DEBUG, "Set object name: {1}, {0}", data->Buf, activeModel->name);
    activeModel->name = data->Buf;
    return 1;
}

std::vector<TESLA::Model*> sceneObjects;

void DrawGUIs()
{
    {
        TESLA::Application::BeginGUI("NoSelect", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs);
        TESLA::Application::EndGUI();
    }
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

void Init()
{
    TESLA::Application::Start(windowWidth, windowHeight, "Editor");
    
    sceneObjects.push_back(ImportModel("cube.obj", "Cube 1"));
    sceneObjects[0]->Translate(glm::vec3(5, 0, 0));

    sceneObjects.push_back(ImportModel("cube.obj", "Cube 2"));
    sceneObjects[1] ->Translate(glm::vec3(2, 2, 2));
}

void Render()
{
    for (TESLA::Model* model : sceneObjects)
        model->Draw();
    
    if(TESLA::Application::ImGUIWantsMouse())
    {
        TESLA::Application::ReturnMouse();
        return;
    }
    
    if(TESLA::Application::GetKey(GLFW_KEY_ESCAPE) == GLFW_PRESS)
        TESLA::ExitApplication();

    if(TESLA::Application::GetKey(GLFW_KEY_F) == GLFW_PRESS)
    {
        glm::vec3 cameraPosition = Camera::cameraPosition;
        glm::vec3 cameraDirection = Camera::cameraDirection;
        
        TESLA_PHYSICS::RaycastResult result;
        if (TESLA_PHYSICS::Raycaster::Raycast(cameraPosition, cameraDirection,
                                              1000, 1000, sceneObjects, result))
        {
            TS_LOG_MESSAGE(TESLA_LOGGER::DEBUG, "Hit {0}", result.hitObject->name);
            activeModel = result.hitObject;
        }
        else
        {
            activeModel = nullptr;
        }
    }
        
    glm::mat4 newView = Camera::CalculateView();
    if(newView != glm::mat4(1))
    {
        view = newView;
    }
    TESLA::Application::SetImGUIFocus("NoSelect");
}

void CleanUp()
{
    TS_LOG_MESSAGE(TESLA_LOGGER::DEBUG, "Application ended");
    sceneObjects.clear();
}