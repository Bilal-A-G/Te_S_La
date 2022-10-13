#include "Te_S_La.h"

int windowHeight = 800;
int windowWidth = 1200;

#define GLOBAL_UP_VECTOR glm::vec3(0, 1, 0)

float nearPlane = 0.1f;
float farPlane = 200.0f;

float angle = 0.0f;
TESLA::Model* suzanne2;
TESLA::Model* suzanne1;

glm::mat4 projection = glm::perspective(glm::radians(70.0f), static_cast<float>(windowWidth)/static_cast<float>(windowHeight), nearPlane, farPlane);
glm::mat4 view = glm::lookAt( glm::vec3(1.5f, 1.0f, 1.5f), glm::vec3(0.0f),GLOBAL_UP_VECTOR);

TESLA::Model* CreateMesh(const char* fileName, const char* modelName)
{
    TESLA::Shader basicShader;
    const GLuint shaderProgram = basicShader.GetProgram();

    return new TESLA::Model(fileName, modelName, shaderProgram, view, projection);
}

void DrawGUIs(){return;}

void Init()
{
    TESLA::Application::Start(windowWidth, windowHeight, "Game");
    
    suzanne1 = CreateMesh("Suzanne.obj", "Monkey1");
    suzanne1->Scale(glm::vec3(0.5, 0.5, 0.5));
    suzanne1->Translate(glm::vec3(-1, 0, 0));

    suzanne2 = CreateMesh("Suzanne.obj", "Monkey2");
    suzanne2->Scale(glm::vec3(0.3,0.3,0.3));
    suzanne2->Translate(glm::vec3(1, 0, 0));
}

void Render()
{
    angle += 1;
    if(angle > 360) angle = 0.0f;
    
    suzanne2->Draw();
    suzanne2->Rotate(angle, GLOBAL_UP_VECTOR);

    suzanne1->Draw();
    suzanne1->Rotate(angle, GLOBAL_UP_VECTOR);
}

void CleanUp()
{
    delete suzanne1;
    delete suzanne2;
}
