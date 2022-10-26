#include "Te_S_La.h"
#include "Camera.h"
#include "physics/Physics.h"
#include "Rendering/Shader.h"
#include"imgui/imgui.h"
#include "GLFW/glfw3.h"

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
    int32_t shaderProgram = basicShader.GetProgram();

    return new TESLA::Model{fileName, modelName, shaderProgram, view, projection};
}

std::vector<TESLA::Model*> sceneObjects;

void DrawGUIs()
{
    {
        ImGui::Begin("Create");
        if(ImGui::Button("Create Object"))
        {
            sceneObjects.push_back(ImportModel("cube.obj", "Joe Mama"));
        }
        ImGui::End();
    }
    {
        ImGui::Begin("Export");
        ImGui::Button("Export Scene To File");
        ImGui::InputText("Scene name", sceneTextBuffer, sizeof(sceneTextBuffer), ImGuiInputTextFlags_AutoSelectAll);
        ImGui::End();
    }
}

TESLA_PHYSICS::RaycastResult result{};

void ProcessInput()
{
    if(TESLA::Input::GetKeyDown(GLFW_KEY_ESCAPE))
    {
        TESLA::ExitApplication();
    }

    if(TESLA::Input::GetMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT))
    {
        if (TESLA_PHYSICS::Raycaster::Raycast(Camera::cameraPosition, Camera::cameraDirection, 1000, 1000, sceneObjects, result))
        {
            TS_LOG_MESSAGE(TESLA_LOGGER::DEBUG, "Hit {0}", result.hitObject->name);
            activeModel = result.hitObject;
        }
        else
        {   
            activeModel = nullptr;
        }
    }
}

void Init()
{
    TESLA::Application::Start(windowWidth, windowHeight, "Editor");
    
    sceneObjects.push_back(ImportModel("Suzanne.obj", "Cube 1"));
    sceneObjects[0]->Translate(glm::vec3(5, 0, 0));

    sceneObjects.push_back(ImportModel("Suzanne.obj", "Cube 2"));
    sceneObjects[1] ->Translate(glm::vec3(2, 2, 2));
    
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

    ProcessInput();
}

void CleanUp()
{
    TS_LOG_MESSAGE(TESLA_LOGGER::DEBUG, "Application ended");
    sceneObjects.clear();
}