/******************************************************************************
	Name: Wes and Zach Harris
	File Name: model_view.cpp
	Synopsis: This file includes an object class that will load a simple model
              from an object file, as well as a main driver that will render
              the loaded models onto the viewing window.  You will also be
              able to dynamically switch between your simple loaded objects.
******************************************************************************/

#include <glm/gtc/type_ptr.hpp>
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

Camera camera;

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
	AXIS ROTATION
******************************************************************************/
void idle() {
    Theta[Axis] += 0.5; // might try using 0.01 intervals

    if (Theta[Axis] > 360.0) {
        Theta[Axis] -= 360.0;
    }
} // end idle()

/******************************************************************************
	CALLBACKS
******************************************************************************/
void framebuffer_size_callback(GLFWwindow* window, int width, int height){

    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0,0,width, height);
}

static void cursorPositionCallback( GLFWwindow *window, double xpos, double ypos )
{
    std::cout << xpos << " : " << ypos << std::endl;
    camera.ProcessMouseMovement(xpos, ypos);
}

void scrollCallback( GLFWwindow *window, double xoffset, double yoffset )
{
    std::cout << xoffset << " : " << yoffset << std::endl;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        Axis = Zaxis;
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        Axis = Xaxis;
    if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
        Axis = Yaxis;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        exit(EXIT_SUCCESS);
    if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, 1);
    }
    if (key == GLFW_KEY_A && action == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, 1);
    }
    if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, 1);
    }
    if (key == GLFW_KEY_D && action == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, 1);
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

/******************************************************************************
	MAIN
******************************************************************************/
int main(){

    int framebufferWidth = 0;
    int framebufferHeight = 0;

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

    // create a window
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

    glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

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
    glfwSetCursorPosCallback( window, cursorPositionCallback );
    glfwSetScrollCallback( window, scrollCallback );

    unsigned char pixels[16 * 16 * 4];
    memset( pixels, 0xff, sizeof( pixels ) );
    GLFWimage image;
    image.width = 16;
    image.height = 16;
    image.pixels = pixels;
    GLFWcursor *cursor = glfwCreateCursor( &image, 0, 0 );
    glfwSetCursor( window, cursor ); // set to null to reset cursor

    // set up the camera and view/projection matrices
    // -----------------------------------------------------------------------
    camera = Camera();

    float fov = 90.f;
    float nearPlane = 0.1f;
    float farPlane = 1000.f;
    glm::mat4 ProjectionMatrix(1.f);

    ProjectionMatrix = glm::perspective(
            glm::radians(fov),
            static_cast<float>(framebufferWidth) / framebufferHeight,
            nearPlane,
            farPlane
    );

    /*INIT UNIFORMS */
    glUseProgram(vao);

    //glUniformMatrix4fv(glGetUniformLocation(vao, "model"), 1, GL_FALSE, glm::value_ptr(ModelMatrix));
    glUniformMatrix4fv(glGetUniformLocation(vao, "view"), 1, GL_FALSE, glm::value_ptr(camera.GetViewMatrix()));
    glUniformMatrix4fv(glGetUniformLocation(vao, "proj"), 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));

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