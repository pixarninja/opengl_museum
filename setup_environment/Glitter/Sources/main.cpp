/******************************************************************************
	Name: Wes and Zach Harris
	File Name: model_view.cpp
	Synopsis: This file includes an object class that will load a simple model
              from an object file, as well as a main driver that will render
              the loaded models onto the viewing window.  You will also be
              able to dynamically switch between your simple loaded objects.
******************************************************************************/

#include "Object.h"

/******************************************************************************

	Shader Set-up

******************************************************************************/

const char *vertexShaderSource = "#version 330\n"
        "in vec4 vPosition;\n"
        "in vec4 vColor;\n"
        "out vec4 color;\n"
        "uniform vec3 theta;\n"
        "void main()\n"
        "{\n"
        "   //Compute the sines and cosines of theta for each of\n"
        "   //the three axes in one computation.\n"
        "   vec3 angles = radians(theta);\n"
        "   vec3 c = cos(angles);\n"
        "   vec3 s = sin(angles);\n"
        "   //Remember: these matrices are column major.\n"
        "   mat4 rx = mat4(1.0, 0.0, 0.0, 0.0,\n"
        "                  0.0, c.x, s.x, 0.0,\n"
        "                  0.0, -s.x, c.x, 0.0,\n"
        "                  0.0, 0.0, 0.0, 1.0);\n"
        "   mat4 ry = mat4(c.y, 0.0, -s.y, 0.0,\n"
        "                  0.0, 1.0, 0.0, 0.0,\n"
        "                  s.y, 0.0, c.y, 0.0,\n"
        "                  0.0, 0.0, 0.0, 1.0);\n"
        "   mat4 rz = mat4(c.z, -s.z, 0.0, 0.0,\n"
        "                  s.z, c.z, 0.0, 0.0,\n"
        "                  0.0, 0.0, 1.0, 0.0,\n"
        "                  0.0, 0.0, 0.0, 1.0);\n"
        "   color = vColor * 1.5;\n"
        "   gl_Position = rz * ry * rx * vPosition;\n"
        "}\0";

const char *fragmentShaderSource = "#version 330\n"
        "in vec4 color;\n"
        "out vec4 fColor;\n"
        "void main()\n"
        "{\n"
        "   fColor = color;\n"
        "}\n\0";

/******************************************************************************

	GLOBAL VARIABLES

******************************************************************************/

// Array of rotation angles (degrees) for each coordinate axis
enum { Xaxis = 0, Yaxis = 1, Zaxis = 2, NumAxes = 3 };
int Axis = Xaxis;

const int NUM_MODELS = 2;

GLfloat Theta[NumAxes] = { 0.0, 0.0, 0.0 };
Object objects[NUM_MODELS] = {
        std::string("/home/pixarninja/Git/opengl_museum/setup_environment/Glitter/Sources/cube.obj"),
        std::string("/home/pixarninja/Git/opengl_museum/setup_environment/Glitter/Sources/first_cut.obj")
};
GLuint vao[NUM_MODELS];
int modelSelection = 0;

// the location of the "theta" shader uniform variable
GLint theta;

// set up our window size
const unsigned int SCR_WIDTH = 700;
const unsigned int SCR_HEIGHT = 700;

/******************************************************************************

	OPENGL INITIALIZATION

******************************************************************************/
void init() {
    // create a vertex array object (vao)
    glGenVertexArrays(NUM_MODELS, vao);

    // Build and compile our shader program
    // ---------- Vertex Shader -----------
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    // ---------- Fragment Shader ----------
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    // Link the shaders to the program
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    // check for linking errors
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED.\n"
                  << infoLog << std::endl;
    }

    // now lets get rid of the shaders since
    // we have linked them to the program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // now let's link all this stuff up to our VAO
    // and prep to display our objects
    glUseProgram(program);
    for(int i = 0; i < NUM_MODELS; i++){
        glBindVertexArray(vao[i]);
        objects[i].load(program);
    }

    glBindVertexArray(vao[0]);
    theta = glGetUniformLocation(program, "theta");

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
    objects[modelSelection].draw();
} // end display()

/******************************************************************************

	KEYBOARD SWITCH COMMANDS

******************************************************************************/
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        exit(EXIT_SUCCESS);
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        modelSelection = (modelSelection + 1) % NUM_MODELS;
        glBindVertexArray(vao[modelSelection]);
    }
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
    Theta[Axis] += 1.0; // might try using 0.01 intervals

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
