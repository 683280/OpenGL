#include <SDL2_main.h>
#include <GLFW_main.h>
//Linux操作系统
#ifdef _LINUX
int main(){
    int width = 800;
    int height = 600;
//  sdl_main(width, height);
    glfw_main(width,height);
}
//Window 32位 和 64 位
#elif defined _WIN32 || defined _WIN64
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
//MAC系统
#elif __APPLE__
int main(){
    int width = 800;
    int height = 600;
//    sdl_main(width, height);    //SDL2
    glfw_main(width,height);  //GLFW
}
#endif