//
// Created by 13342 on 2017/11/3.
//

#ifndef OPENGL_OPENGL_H
#define OPENGL_OPENGL_H
#include <Shader.h>
#include <glm/vec3.hpp>
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SOIL.h>
#include <Camera.h>

class OpenGL {
public:
//    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
//    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
//    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
//    GLfloat fov =  45.0f;
    bool keys[1024];
    Camera* camera ;
public:
    OpenGL(int width,int height);
    void draw();
    double get_time();
private:
    int width,height;
    Shader* shader;
    GLuint texture1,texture2;
    GLuint VAO,lightVAO;
    unsigned long start_t;
    GLfloat deltaTime = 0.0f;   // 当前帧遇上一帧的时间差
    GLfloat lastFrame = 0.0f;   // 上一帧的时间

private:
    void do_movement();
};


#endif //OPENGL_OPENGL_H
