#include <SDL2_main.h>
#include <GLFW_main.h>
#include <winnt.h>

int WinMain(HINSTANCE hInstance,      // handle to current instance
                HINSTANCE hPrevInstance,  // handle to previous instance
                LPSTR lpCmdLine,          // command line
                int nCmdShow) {
    int width = 800;
    int height = 600;
//    sdl_main(width, height);
    glfw_main(width,height);
}