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
//#include <glad/glad.h>

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

    //Shader(Rectangle& );

    void useProgram();

    //void settingTex(string tex, int ind);
    void settingTex();

    void setModelMatrix(const glm::mat4& m);

    void setViewMatrix(const glm::mat4& v);

    void settingMatrix(const glm::mat4& v);

    //void setColor();
};

class lampShader {
private:
    unsigned int lampShaderProgram;
public:
    lampShader();

    ~lampShader();
};


class Buffer {
private:
    unsigned int vao;
public:
    Buffer(const vector<float>& vertices, const vector<int>& indices);

    void bind();

    ~Buffer();
};

unsigned int buildTexture(const char* path);

//class texture {
//private:
//    const char path;
//public:
//    texture(const char& info);
//
//    void build();
//};

/*
class Rectangle {
private:
    Shader& shaderProgram;
    Buffer& buffer;
    glm::vec3 s;
    glm::vec3 t;

public:
    Rectangle(Shader& shader, Buffer& buffer);

    virtual void color(float r, float g, float b);

    //virtual void rotate();

    virtual void scale(float x, float y, float z);

    virtual void setPosition(float x, float y, float z);

    virtual void draw();
};*/

/*
class Player : public Rectangle {
public:
    Player(Shader& shader, Buffer& buffer);

    //int score();
};*/