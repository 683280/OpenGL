cmake_minimum_required(VERSION 3.8)
project(OpenGl)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)
link_directories(lib)
set(SOURCE_FILES main.cpp Shader.cpp OpenGL.cpp GLFW_main.cpp SDL2_main.cpp)
add_executable(OpenGl ${SOURCE_FILES})
target_link_libraries(OpenGl SDL2 glfw3 glew32 SOIL opengl32 )