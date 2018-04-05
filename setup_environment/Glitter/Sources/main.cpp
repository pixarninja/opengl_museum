/******************************************************************************
	Name: Wes and Zach Harris
	File Name: model_view.cpp
	Synopsis: This file includes an object class that will load a simple model
              from an object file, as well as a main driver that will render
              the loaded models onto the viewing window.  You will also be
              able to dynamically switch between your simple loaded objects.
******************************************************************************/

#include "camera.h"
#include "mesh.h"
#include "model.h"
#include "object.h"
#include "shader.h"

/******************************************************************************

	Shader Set-up

******************************************************************************/

const char *vertexShaderSource = "/home/pixarninja/Git/opengl_museum/setup_environment/Glitter/Sources/vertex.shader";
const char *fragmentShaderSource = "/home/pixarninja/Git/opengl_museum/setup_environment/Glitter/Sources/fragment.shader";
const char *modelSource = "/home/pixarninja/Git/opengl_museum/setup_environment/Glitter/Sources/cube2_sub_disp.obj";

/******************************************************************************

	GLOBAL VARIABLES

******************************************************************************/

// Array of rotation angles (degrees) for each coordinate axis
enum { Xaxis = 0, Yaxis = 1, Zaxis = 2, NumAxes = 3 };
int Axis = Xaxis;

GLfloat Theta[NumAxes] = { 0.0, 0.0, 0.0 };
GLuint vao;
Shader shader;
Model model;
Texture* gTexture = NULL;

// the location of the "theta" shader uniform variable
GLint theta;

// set up our window size
const unsigned int SCR_WIDTH = 500;
const unsigned int SCR_HEIGHT = 500;

/******************************************************************************

	OPENGL INITIALIZATION

******************************************************************************/
void init() {
    // create a vertex array object (vao)
    glGenVertexArrays(1, &vao);

    // initialize and use the shader we initialized globally
    shader.create(vertexShaderSource, fragmentShaderSource);
    shader.use();

    // do the same for the model
    model.create(modelSource);

    glBindVertexArray(vao);
    theta = glGetUniformLocation(shader.ID, "theta");

    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0, 1.0, 1.0,1.0);

} // end init()

/******************************************************************************

	DISPLAY LOADED OBJECT

*******************************************************************************/
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUniform3fv(theta, 1, Theta);

    // draw the currently loaded model
    model.draw(shader);
} // end display()

/******************************************************************************

	KEYBOARD SWITCH COMMANDS

******************************************************************************/
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        exit(EXIT_SUCCESS);
} // end key_callback()

/******************************************************************************

	MOUSE COMMANDS

******************************************************************************/
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        Axis = Zaxis;
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        Axis = Xaxis;
    if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
        Axis = Yaxis;
} // end mouse_button_callback()

/******************************************************************************

	AXIS ROTATION

******************************************************************************/
void idle() {
    Theta[Axis] += 0.5; // might try using 0.01 intervals

    if (Theta[Axis] > 360.0) {
        Theta[Axis] -= 360.0;
    }
} // end idle()

/******************************************************************************

	MAIN

******************************************************************************/
int main(){

    // glfw: initialize and configure
    // -----------------------------------------------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // -----------------------------------------------------------------------
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // create a windowed window ... something that is not
    // full screen
    // -----------------------------------------------------------------------
    GLFWwindow* window =
            glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,
                             "Harris_Harris Object Viewer",
                             nullptr, nullptr
            );
    if(window == nullptr){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // make the OpenGL context active
    // -----------------------------------------------------------------------
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // call init()
    // -----------------------------------------------------------------------
    init();

    // set up the requirements for our key/mouse clicks
    // -----------------------------------------------------------------------
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    // glfw uses a "closed event" loop, which means you only have to handle
    // events when you need to
    // -----------------------------------------------------------------------
    while(!glfwWindowShouldClose(window)){
        //retrieve window events
        glfwSwapBuffers(window);
        display();
        idle();
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources
    // -----------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
    if(glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    if(glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    if(glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }
}

//glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height){

    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0,0,width, height);
}
