//
// Created by 13342 on 2017/11/3.
//
#include <SDL2_main.h>
#include <OpenGL.h>
int sdl_key_callback(SDL_Keycode key) {
    switch (key){
        case SDLK_a:
            break;
        case SDLK_w:
            break;
        case SDLK_s:
            break;
        case SDLK_d:
            break;
    }
}
int sdl_main(int WIDTH, int HEIGHT) {
    SDL_Init(SDL_INIT_VIDEO);
    auto window = SDL_CreateWindow("SDL2 OpenGL",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT,SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);
    SDL_GL_CreateContext(window);
    auto opengl = new OpenGL(WIDTH,HEIGHT);
    SDL_Event event;

    while(1){
        SDL_PollEvent(&event);
        if(event.type == SDL_QUIT){
            break;
        } else if(event.type == SDL_KEYDOWN){
            sdl_key_callback(event.key.keysym.sym);
        }
        printf("%f\n",opengl->get_time());
        opengl->draw();
        SDL_GL_SwapWindow(window);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
