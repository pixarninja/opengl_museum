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

const char *vertexShaderSource = "/home/zach/Git/NMT/3D-Graphics/opengl_museum/setup_environment/Glitter/Sources/vertex.shader";
const char *fragmentShaderSource = "/home/zach/Git/NMT/3D-Graphics/opengl_museum/setup_environment/Glitter/Sources/fragment.shader";
const char *modelSource = "/home/zach/Git/NMT/3D-Graphics/opengl_museum/setup_environment/Glitter/Sources/samich.obj";

/******************************************************************************
	GLOBAL VARIABLES
******************************************************************************/
Camera camera;
GLuint vao;

// set up our window size
const unsigned int SCR_WIDTH = 500;
const unsigned int SCR_HEIGHT = 500;

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
    // create a vertex array object (vao)
    glGenVertexArrays(1, &vao);

    // initialize and use the shader we initialized globally
    Shader shader(vertexShaderSource, fragmentShaderSource);
    shader.use();

    // do the same for the model
    Model model(modelSource);

    glBindVertexArray(vao);
    glClearColor(1.0, 1.0, 1.0, 1.0);

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
    float nearPlane = 1.0f;
    float farPlane = 100.f;
    glm::mat4 ProjectionMatrix(1.f);

    ProjectionMatrix = glm::perspective(
            glm::radians(camera.Zoom),
            (float) SCR_WIDTH / (float) SCR_HEIGHT,
            nearPlane,
            farPlane
    );

    /*INIT UNIFORMS */
    glUseProgram(vao);

    //glUniformMatrix4fv(glGetUniformLocation(vao, "model"), 1, GL_FALSE, glm::value_ptr(ModelMatrix));
    glUniformMatrix4fv(glGetUniformLocation(vao, "view"), 1, GL_FALSE, glm::value_ptr(camera.GetViewMatrix()));
    glUniformMatrix4fv(glGetUniformLocation(vao, "proj"), 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));

    cout << camera.GetViewMatrix()[0][0] << endl;

    // glfw uses a "closed event" loop, which means you only have to handle
    // events when you need to
    // -----------------------------------------------------------------------
    while(!glfwWindowShouldClose(window)){
        //retrieve window events
        glfwSwapBuffers(window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw the currently loaded model
        model.Draw(shader);

        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources
    // -----------------------------------------------------------------------
    glfwTerminate();
    return 0;
}