//
// Created by 13342 on 2017/11/3.
//

#include <ctime>
#include "OpenGL.h"

#include <GLFW/glfw3.h>
#include <sys/time.h>

#ifdef WIN32
#include <afxres.h>
#endif

float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};
glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
};
long get_unix_time(){
#ifdef WIN32
    return GetTickCount();
#else __APPLE__
    struct timeval t;
    gettimeofday(&t,NULL);
    return t.tv_sec * 1000 + t.tv_usec / 1000;
#endif
}
OpenGL::OpenGL(int width,int height) {

    start_t = get_unix_time();
    this->width = width;
    this->height = height;
    camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return;
    }
    std::cout << glGetString(GL_VERSION) << std::endl;
    glViewport(0, 0, width, height);
    //OpenGL 开启深度测试
    glEnable(GL_DEPTH_TEST);
    shader = new Shader("./glsl/vertexShader.glsl","./glsl/fragmentShader.glsl");
    light_shader = new Shader("./glsl/light.vs.glsl","./glsl/light.fs.glsl");


    GLuint VBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices,GL_STATIC_DRAW);

    //0
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6 * sizeof(GLfloat),(GLvoid*)0);
    glEnableVertexAttribArray(0);


    glBindVertexArray(0);
    glGenVertexArrays(1,&lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3* sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
    //texture
    glGenTextures(1,&texture1);
    glGenTextures(1,&texture2);
    glBindTexture(GL_TEXTURE_2D,texture1);
    glUniform1i(glGetUniformLocation(shader->Program, "ourTexture1"), 0);
    int width1, height1;
    unsigned char* image = SOIL_load_image("./container.jpg", &width1, &height1, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width1,height1,0,GL_RGB,GL_UNSIGNED_BYTE,image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindTexture(GL_TEXTURE_2D,texture2);
    glUniform1i(glGetUniformLocation(shader->Program, "ourTexture2"), 0);
    image = SOIL_load_image("awesomeface.png", &width1, &height1, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width1,height1,0,GL_RGB,GL_UNSIGNED_BYTE,image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);

//    glTextureParameteri(texture1,GL_TEXTURE_WRAP_S,GL_REPEAT);
//    glTextureParameteri(texture1,GL_TEXTURE_WRAP_T,GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}
void OpenGL::do_movement() {
    GLfloat currTime = get_time();
    deltaTime = currTime - lastFrame;
    lastFrame = currTime;
    // 摄像机控制
    if(keys[FORWARD])
        camera->ProcessKeyboard(FORWARD, deltaTime);
    if(keys[BACKWARD])
        camera->ProcessKeyboard(BACKWARD, deltaTime);
    if(keys[LEFT])
        camera->ProcessKeyboard(LEFT, deltaTime);
    if(keys[RIGHT])
        camera->ProcessKeyboard(RIGHT, deltaTime);
}
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
void OpenGL::draw() {
    do_movement();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //draw
//        glBindTexture(GL_TEXTURE_2D, texture1);
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, texture1);
//    glUniform1i(glGetUniformLocation(shader->Program, "ourTexture1"), 0);
//    glActiveTexture(GL_TEXTURE1);
//    glBindTexture(GL_TEXTURE_2D, texture2);
//    glUniform1i(glGetUniformLocation(shader->Program, "ourTexture2"), 1);

    light_shader->Use();
    light_shader->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
    light_shader->setVec3("lightColor",  1.0f, 1.0f, 1.0f);
    light_shader->setVec3("lightPos", lightPos);
    glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)width / (float)height, 0.1f, 100.0f);
    glm::mat4 view = camera->GetViewMatrix();
    light_shader->setMat4("projection", projection);
    light_shader->setMat4("view", view);

    // world transformation
    glm::mat4 model;
    light_shader->setMat4("model", model);

    // render the cube
    glBindVertexArray(lightVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);


    shader->Use();
    shader->setMat4("projection", projection);
    shader->setMat4("view", view);
    model = glm::mat4();
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
    shader->setMat4("model", model);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
//    glm::mat4 transform;
//    // Create transformations
//    glm::mat4 model;
//    glm::mat4 view;
//    glm::mat4 projection;
//
//    view = camera->GetViewMatrix();
//
//    projection = glm::perspective(glm::radians(camera->Zoom), (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
//    // Get their uniform location
//    GLint modelLoc = glGetUniformLocation(shader->Program, "model");
//    GLint viewLoc = glGetUniformLocation(shader->Program, "view");
//    GLint projLoc = glGetUniformLocation(shader->Program, "projection");
//    // Pass them to the shaders
//    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//    // Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
//    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
//    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//    glBindVertexArray(VAO);
//    glDrawArrays(GL_TRIANGLES, 0, 36);
//
//    glBindVertexArray(lightVAO);
//    glm::translate(model,glm::vec3(1.0,0.0,-1.0));
//    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//    glDrawArrays(GL_TRIANGLES, 0, 36);
//    glBindVertexArray(0);
}

double OpenGL::get_time(){
    unsigned long t;
    t = get_unix_time();

    double time = (t - start_t) / 1000.0;
    return time;
}