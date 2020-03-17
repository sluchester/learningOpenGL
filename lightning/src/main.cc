#include "cameraYaw.h"

bool firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = screenWidth / 2;
float lastY = screenHeight / 2;
float fov = 45.0f;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

void processInput(GLFWwindow* window, glm::vec3& _cameraPos, glm::vec3& _cameraFront, glm::vec3& _cameraUp, float& _dTime) {

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    const float cameraSpeed = 2.5f * _dTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        _cameraPos += cameraSpeed * _cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        _cameraPos -= cameraSpeed * _cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        _cameraPos -= glm::normalize(glm::cross(_cameraFront, _cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        _cameraPos += glm::normalize(glm::cross(_cameraFront, _cameraUp)) * cameraSpeed;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int Width, int Height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, Width, Height);
}

//Shader* _objShader = nullptr;

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    //direction.y = sin(glm::radians(pitch));
    direction.y = 0.0f;
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);

    //COLOCAR COMO UMA FUNÇÃO
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    if (fov > 1.0f && fov < 45.0f)
        fov -= yoffset;
    else if (fov <= 1.0f)
        fov = 1.0f;
    else if (fov >= 45.0f)
        fov = 45.0f;
}

GLFWwindow* initGL() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback); //projection
    glfwSetScrollCallback(window, scroll_callback); //cameraFront

    glewExperimental = true;	//http://glew.sourceforge.net/basic.html
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return nullptr;
    }

    return window;
}

GLFWwindow* window = nullptr;

//program begins
int main() {
    
    window = initGL();
    if (window == nullptr)
        return -1;

    glEnable(GL_DEPTH_TEST);

    Shader objShader;
    //_objShader = &objShader;
    objShader.useProgram();

    //std::cout << "pass here" << endl;

    vector<float> vertices = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    vector<int> indices = {
        0, 1, 3,
        1, 2, 3
    };

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    Buffer objBuffer(vertices, indices);

    //std::cout << "pass here" << endl;


    // locating and opening the image files
    const char* path = "C:/Users/luan.conceicao/source/repos/cameraYaw/image/container.jpg";
    const char* path2 = "C:/Users/luan.conceicao/source/repos/cameraYaw/image/awesomeface.png";

    // textures id's
    auto texture1 = buildTexture(path);
    auto texture2 = buildTexture(path2);

    //std::cout << "texture 1 = " << texture1 << endl;
    //std::cout << "texture 2 = " << texture2 << endl;

    objShader.useProgram();
    objShader.settingTex();

    //glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    //glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    //glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;


    while (!glfwWindowShouldClose(window)) {

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window, cameraPos, cameraFront, cameraUp, deltaTime);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

        // binding textures
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        objShader.useProgram();
        //objShader.setColor();

        glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
        objShader.settingMatrix(projection);

        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        objShader.setViewMatrix(view);

        objBuffer.bind();

        for (unsigned int i = 0; i < 10; i++) {

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            objShader.setModelMatrix(model);
            
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    objBuffer.~Buffer();

    glfwTerminate();

    return 0;
  
    }