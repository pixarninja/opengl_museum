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
const char *modelSource = "/home/pixarninja/Git/opengl_museum/setup_environment/Glitter/Sources/testRickHouse.obj";

/******************************************************************************
	GLOBAL VARIABLES
******************************************************************************/
Camera camera;
Model model;
double prevX;
double prevY;
bool init = true;
double currTime = 0;
double deltaTime = 0;

// set up our window size
unsigned int SCR_WIDTH = 700;
unsigned int SCR_HEIGHT = 700;

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
    std::cout << xpos << ", " << ypos << std::endl;
    if (init) {
        // need to initialize starting position, so first frame of input is not used
        //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        init = false;
    } else {
        // move camera based on changes in cursor position
        camera.ProcessMouseMovement((SCR_WIDTH / 100) * xpos - prevX, prevY - (SCR_HEIGHT / 150) * ypos);
    }
    prevX = (SCR_WIDTH / 100) * xpos;
    prevY = (SCR_HEIGHT / 150) * ypos;
}

void scrollCallback( GLFWwindow *window, double xoffset, double yoffset )
{
    std::cout << yoffset << std::endl;
    camera.ProcessMouseScroll(yoffset);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    ;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        exit(EXIT_SUCCESS);
    if (key == GLFW_KEY_N) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (key == GLFW_KEY_A) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (key == GLFW_KEY_M) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (key == GLFW_KEY_D) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
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
    if(key == GLFW_KEY_S) {
        camera.ProcessKeyboard(DOWN, deltaTime);
    }
    if(key == GLFW_KEY_W) {
        camera.ProcessKeyboard(UP, deltaTime);
    }
    if(key == GLFW_KEY_RIGHT) {
        camera.ProcessKeyboard(ROTRIGHT, deltaTime);
    }
    if(key == GLFW_KEY_LEFT) {
        camera.ProcessKeyboard(ROTLEFT, deltaTime);
    }
    if(key == GLFW_KEY_UP) {
        camera.ProcessKeyboard(ROTUP, deltaTime);
    }
    if(key == GLFW_KEY_DOWN) {
        camera.ProcessKeyboard(ROTDOWN, deltaTime);
    }
    if(key == GLFW_KEY_PERIOD) {
        camera.ProcessKeyboard(TILTRIGHT, deltaTime);
    }
    if(key == GLFW_KEY_COMMA) {
        camera.ProcessKeyboard(TILTLEFT, deltaTime);
    }
    if(glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
        model = Model("/home/pixarninja/Git/opengl_museum/setup_environment/Glitter/Sources/fourth_cut.obj");
    }
    if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        model = Model("/home/pixarninja/Git/opengl_museum/setup_environment/Glitter/Sources/third_cut.obj");
    }
    if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        model = Model("/home/pixarninja/Git/opengl_museum/setup_environment/Glitter/Sources/cube3.obj");
    }
    if(glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
        model = Model("/home/pixarninja/Git/opengl_museum/setup_environment/Glitter/Sources/pikachu.obj");
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
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    SCR_WIDTH = mode->width;
    SCR_HEIGHT = mode->height;
    GLFWwindow* window =
            glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,
                             "Harris_Harris Object Viewer",
                             //glfwGetPrimaryMonitor(), nullptr
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

    glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    //glfwSetCursorPosCallback( window, cursorPositionCallback );
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetScrollCallback( window, scrollCallback );

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // initialize shader
    Shader shader = Shader(vertexShaderSource, fragmentShaderSource);
    shader.use();
    // initialize camera
    camera = Camera();

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    model = Model(modelSource);

    unsigned char pixels[4 * 4 * 4];
    memset( pixels, 0xff, sizeof( pixels ) );
    GLFWimage image;
    image.width = 4;
    image.height = 4;
    image.pixels = pixels;
    GLFWcursor *cursor = glfwCreateCursor( &image, 0, 0 );
    glfwSetCursor( window, cursor ); // set to null to reset cursor

    // glfw uses a "closed event" loop, which means you only have to handle
    // events when you need to
    // -----------------------------------------------------------------------
    while(!glfwWindowShouldClose(window)){
        double prevTime = currTime;
        currTime = glfwGetTime();
        deltaTime = currTime - prevTime;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.use();

        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, (float *)glm::value_ptr(camera.GetViewMatrix()));
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "proj"), 1, GL_FALSE, (float *)glm::value_ptr(glm::perspective(glm::radians(camera.Zoom), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 100.0f)));

        // draw the currently loaded model
        model.Draw(shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources
    // -----------------------------------------------------------------------
    glfwTerminate();
    return 0;
}