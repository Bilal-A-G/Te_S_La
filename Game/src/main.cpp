#include "iostream"

namespace Test
{
    __declspec(dllimport) void Print();
}

int main(int argc, char* argv[])
{
    Test::Print();
}
