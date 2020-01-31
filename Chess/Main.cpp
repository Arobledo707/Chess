#include "Application.h"
#include <conio.h>
#include <vld.h>

int main(int argc, char* argv[]) 
{
    Application app;
    app.Initialize();
    app.Run();
    _getch();
    return 0;
}