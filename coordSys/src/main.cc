#include "coordSys.h"


//void processInput(GLFWwindow* window, Shader& shaderProgram, Buffer& objBuffer){
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int Width, int Height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, Width, Height);
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

    glewExperimental = true;	//http://glew.sourceforge.net/basic.html
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return nullptr;
    }
    /*
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }*/

    return window;
}

GLFWwindow* window = nullptr;



//program begins
int main() {
    
    window = initGL();
    if (window == nullptr)
        return -1;

    Shader objShader;
    objShader.useProgram();

    std::cout << "pass here" << endl;

    //1st time
    /*vector<float> vertices = {
        // positions          // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
    };*/

    //2nd time
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

    Buffer objBuffer(vertices, indices);
    //objBuffer.bind();


    std::cout << "pass here" << endl;


    // locating and opening the image files
    const char* path = "C:/Users/luan.conceicao/source/repos/coordSys/image/container.jpg";
    const char* path2 = "C:/Users/luan.conceicao/source/repos/coordSys/image/awesomeface.png";

    // textures id's
    auto texture1 = buildTexture(path);
    auto texture2 = buildTexture(path2);

    std::cout << "texture 1 = " << texture1 << endl;
    std::cout << "texture 2 = " << texture2 << endl;

    objShader.useProgram();
    objShader.settingTex();

    //allow the gl depth test
        //it's disable by default
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) {

        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.2f, 0.2f, 1.0f);
        

        // binding textures
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        objShader.useProgram();
        //objShader.setColor();

        //creating transformations through matrix
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        //1st time -> model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        //2nd time
        model = glm::rotate(model, 4 * (float)glfwGetTime() * glm::radians(70.0f), glm::vec3(0.5f, 1.0f, 0.0f));
       /* for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                std::cout << " " << model[i][j];
            }
            std::cout << endl;
        }

        std::cout << endl;*/

        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        /*
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                std::cout << " " << view[i][j];
            }
            std::cout << endl;
        }

        std::cout << endl;
        */

        projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
        /*
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                std::cout << " " << projection[i][j];
            }
            std::cout << endl;
        }

        std::cout << endl;*/


        objShader.setModelMatrix(model);
        objShader.setViewMatrix(view);
        objShader.settingMatrix(projection);

        objBuffer.bind();
        //1st time -> glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //2nd timne
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();

    }
    objBuffer.~Buffer();

    glfwTerminate();

    return 0;
        
    }