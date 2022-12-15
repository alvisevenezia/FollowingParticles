#include "openglUtils.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {

    glad_glViewport(0, 0, width, height);

}

void MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam){
    
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
        (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
        type, severity, message);

}

void processInput(GLFWwindow* window) {

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {

        glfwSetWindowShouldClose(window, true);

    }

}

GLFWwindow* initGLProcess(int majorVersion, int minorVersion,int width,int height){

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   
    GLFWwindow* window = glfwCreateWindow(width, height, "PathGenerator", NULL, NULL);

    if (window == NULL) {

        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;

    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {

        std::cout << "Failed ot initialize GLAD" << std::endl;

    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);
    
    return window;
    
}
