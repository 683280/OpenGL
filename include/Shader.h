//
// Created by 13342 on 2017/10/20.
//

#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
class Shader
{
public:
    // 程序ID
    GLuint Program;
    // 构造器读取并构建着色器
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    void setVec3(const char* name,float x,float y,float z);
    void setVec3(const char* name,glm::vec3 vec3);
    void setMat4(const GLchar* name,glm::mat4 m);
    // 使用程序
    void Use();
};


#endif //OPENGL_SHADER_H
