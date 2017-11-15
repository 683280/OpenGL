//
// Created by 13342 on 2017/11/3.
//
#include <SDL2_main.h>
#include <OpenGL.h>
OpenGL* opengl;
int sdl_key_callback(SDL_Keycode key,int i) {
    Camera_Movement k ;


    if(key == SDLK_w)
        k = FORWARD;
    else if(key == SDLK_s)
        k = BACKWARD;
    else if(key == SDLK_a)
        k = LEFT;
    else if(key == SDLK_d)
        k = RIGHT;
    else
        k == -1;
    if (k == -1){
        return -1;
    }
    if (i == 1)
        opengl->keys[k] = true;
    else if (i == 0)
        opengl->keys[k] = false;
    return 0;
}
bool firstMousee = true;
const int WIDTH = 800,HEIGHT = 600;
GLfloat lastXx  =  WIDTH  / 2.0;
GLfloat lastYy  =  HEIGHT / 2.0;
void mouse_callback(double xpos, double ypos){
    if (firstMousee)
    {
        lastXx = xpos;
        lastYy = ypos;
        firstMousee = false;
    }

    float xoffset = xpos - lastXx;
    float yoffset = lastYy - ypos; // reversed since y-coordinates go from bottom to top

    lastXx = xpos;
    lastYy = ypos;

    opengl->camera->ProcessMouseMovement(xoffset, yoffset);
}
int sdl_main(int WIDTH, int HEIGHT) {
    if (SDL_Init (SDL_INIT_EVENTS | SDL_INIT_VIDEO) < 0){
        printf ("sdl init error: %s", SDL_GetError());
        return -1;
    }
    //使用Opengl 3.3以上
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    auto window = SDL_CreateWindow("SDL2 OpenGL",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT,SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);
    SDL_GL_CreateContext(window);
//    SDL_ShowCursor(0);//隐藏光标
    SDL_SetRelativeMouseMode(SDL_TRUE);
    opengl = new OpenGL(WIDTH,HEIGHT);
    SDL_Event event;

    while(1){
        SDL_PollEvent(&event);
        switch (event.type){
            case SDL_QUIT:
                goto end;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    goto end;
                sdl_key_callback(event.key.keysym.sym,1);
                break;
            case SDL_KEYUP:
                sdl_key_callback(event.key.keysym.sym,0);
                break;
            case SDL_MOUSEMOTION:
                mouse_callback(event.motion.x,event.motion.y);
//                opengl->camera->ProcessMouseMovement(event.motion.xrel, event.motion.yrel);
                break;
            case SDL_MOUSEWHEEL:
                std::cout << event.wheel.y << std::endl;
                opengl->camera->ProcessMouseScroll(event.wheel.y);
                break;
        }

        opengl->draw();
        SDL_GL_SwapWindow(window);
    }
    end:
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
