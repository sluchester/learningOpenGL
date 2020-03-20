#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm//gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//CREATE A NEW BUFFER CLASS FOR THE LAMP

#define screenWidth 800
#define screenHeight 600

using namespace std;

GLFWwindow* initGL();

class lightningShader {
private:
    unsigned int lightShaderProgram;
public:
    lightningShader();

    ~lightningShader();

    void lightUseProgram();

    //void lightSettingTex();

    void lightSetObjVec3(float x, float y, float z);

    void lightSetVec3(float x, float y, float z);

    void lightSetModelMatrix(const glm::mat4& m);

    void lightSetViewMatrix(const glm::mat4& v);

    void lightSettingMatrix(const glm::mat4& v);

    //void setColor();
};

class lightBuffer {
private:
    unsigned int lightVAO;
public:
    lightBuffer(const vector<float>& vertices);

    void lightBind();

    ~lightBuffer();
};

/*-------------------------------------------------
*                   lamp part
--------------------------------------------------*/
class lampShader {
private:
    unsigned int lampShaderProgram;
public:
    lampShader();

    ~lampShader();

    void lampUseProgram();

    void lampSetModelMatrix(const glm::mat4& m);

    void lampSetViewMatrix(const glm::mat4& v);

    void lampSettingMatrix(const glm::mat4& p);
};


class lampBuffer {
private:
    unsigned int lampVAO;
public:
    lampBuffer();

    void lampBind();

    ~lampBuffer();
};

//unsigned int buildTexture(const char* path);

//class texture {
//private:
//    const char path;
//public:
//    texture(const char& info);
//
//    void build();
//};