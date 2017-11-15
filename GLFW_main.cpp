//
// Created by 13342 on 2017/11/3.
//
#include <GLFW_main.h>


const int WIDTH = 800,HEIGHT = 600;
GLfloat lastX  =  WIDTH  / 2.0;
GLfloat lastY  =  HEIGHT / 2.0;

OpenGL* openGL;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // 当用户按下ESC键,我们设置window窗口的WindowShouldClose属性为true
    // 关闭应用程序
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024)
    {
        Camera_Movement k ;

        if(key == GLFW_KEY_W)
            k = FORWARD;
        if(key == GLFW_KEY_S)
            k = BACKWARD;
        if(key == GLFW_KEY_A)
            k = LEFT;
        if(key == GLFW_KEY_D)
            k = RIGHT;
        if (action == GLFW_PRESS)
            openGL->keys[k] = true;
        else if (action == GLFW_RELEASE)
            openGL->keys[k] = false;
    }
}
bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    openGL->camera->ProcessMouseMovement(xoffset, yoffset);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    openGL->camera->ProcessMouseScroll(yoffset);
}

int glfw_main(int WIDTH, int HEIGHT) {
    glfwInit();
    //使用Opengl 3.3以上
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //创建窗口
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GLFW OpenGL", nullptr, nullptr);

    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetKeyCallback(window, key_callback);

    openGL = new OpenGL(width,height);
    while (!glfwWindowShouldClose(window)){
        glfwPollEvents();
        openGL->draw();
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}
