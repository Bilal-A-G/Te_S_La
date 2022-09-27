#include"glad/glad.h"
#include"GLFW/glfw3.h"

#include<iostream>

int main(int argc, char* argv[])
{
    glfwInit()
#ifdef PS_DEBUG
    == GLFW_TRUE ?
    std::cout << "GLFW initialized \n" : std::cout <<"GLFW failed to initialize \n";
#elif PS_RELEASE
    ;
#endif

    
}
