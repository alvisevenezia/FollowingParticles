// PathGenerator.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <ctime>
#include "shader.h"
#include "track.h"
#include "utils/spawnUtils.h"

#define WIDTH 1920
#define HEIGHT 1080
#define FRAME_RATE 120
#define NUMBER 1024*1024*3
#define WORK_GROUP_SIZE 1024

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {

    glad_glViewport(0, 0, width, height);

}

void MessageCallback(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam)
{
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
        (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
        type, severity, message);
    
}

void processInput(GLFWwindow* window) {

    if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS) {

        glfwSetWindowShouldClose(window, true);

    }

}

int main()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "PathGenerator", NULL, NULL);

    if (window == NULL) {

        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;

    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {

        std::cout << "Failed ot initialize GLAD" << std::endl;

    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Shader shaderProgram("./shaders/basic_vertex_shader.glsl", "./shaders/fragment_shader.glsl");
    Shader computeProgram("./shaders/compute_shader.glsl");
    Shader decayShader("./shaders/map_update_shader.glsl");
	
    int workGroup = NUMBER/WORK_GROUP_SIZE;
    printf("%d\n", workGroup);
    

    glPointSize(1.0f);

    float* particles = (float*)calloc(NUMBER * 3, sizeof(float));
    float* map = (float*)calloc(WIDTH * HEIGHT,sizeof(float));

    srand(time(NULL));

    auto start = std::chrono::system_clock::now();
    float radius = 400.0f;
	float x = 0.0f;
    
	genType type = middle_in_donut;

    for (int i = 0; i < NUMBER; i++) {

        int x = float(rand() % WIDTH);
        int y = float(rand() % HEIGHT);
        
        if (type == middle_in_circle) {

            while (powf(x - (WIDTH / 2), 2.0f) + powf(y - (HEIGHT / 2), 2.0f) > powf(radius, 2.0f) || (x == WIDTH / 2 || y == HEIGHT / 2)) {
                x = float(rand() % WIDTH);
                y = float(rand() % HEIGHT);
            }
            
        }
		else if (type == middle_in_square) {
			while (x < WIDTH / 2 - radius || x > WIDTH / 2 + radius || y < HEIGHT / 2 - radius || y > HEIGHT / 2 + radius) {
				x = float(rand() % WIDTH);
				y = float(rand() % HEIGHT);
			}
		}
		else if (type == middle_in_triangle) {
			while (!((y > HEIGHT/2 - 250) && 1.5 * (x - WIDTH / 2 + 500) > y && -1.5 *(x-WIDTH/2 - 500) > y)) {
				x = float(rand() % WIDTH);
				y = float(rand() % HEIGHT);
			}
        }
        else if (type == middle_in_donut) {

            while (powf(x - (WIDTH / 2), 2.0f) + powf(y - (HEIGHT / 2), 2.0f) > powf(radius, 2.0f) || (x == WIDTH / 2 || y == HEIGHT / 2)
                ||
                powf(x - (WIDTH / 2), 2.0f) + powf(y - (HEIGHT / 2), 2.0f) < powf((radius - 100), 2.0f) || (x == WIDTH / 2 || y == HEIGHT / 2)) {
                x = float(rand() % WIDTH);
                y = float(rand() % HEIGHT);
            }

        }
        
        
        particles[i * 3] = x;
        particles[i * 3 + 1] = y;

        //generate random angle betwenn 0 and 2pi
		float angle = float(rand() % 628) / 100.0f;
		
		particles[i * 3 + 2] = angle;

   }


    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "elapsed time: " << elapsed_seconds.count() << "s"
        << std::endl;

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);

    unsigned int VBO,VAO,mapBuffer;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, NUMBER *3* sizeof(float), particles, GL_DYNAMIC_COPY);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, VBO);

    
    glGenBuffers(1, &mapBuffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, mapBuffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, WIDTH * HEIGHT * sizeof(float), map, GL_DYNAMIC_COPY);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, mapBuffer);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
    
    double time = glfwGetTime();
    
    shaderProgram.use();
    shaderProgram.setInt("WIDTH", WIDTH);
    shaderProgram.setInt("HEIGHT", HEIGHT);

    computeProgram.use();
	//set the offset angle of compute shader to 30 degree in radian
	computeProgram.setFloat("offsetAngle", 0.523599f);
    computeProgram.setInt("snifSize", 3);
    computeProgram.setInt("snifRange",4);
    computeProgram.setFloat("seed", rand());
    computeProgram.setInt("WIDTH", WIDTH);
    computeProgram.setInt("HEIGHT", HEIGHT);

    decayShader.use();
    decayShader.setFloat("decayRate", 0.01f);
    
    //render loop
    while (!glfwWindowShouldClose(window)) {

        
        
        if (glfwGetTime() - time > 1/ FRAME_RATE) {

            time = glfwGetTime();

            //check for input
            processInput(window);

            //rendering stuff
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            shaderProgram.use();
            shaderProgram.setInt("WIDTH", WIDTH);
            shaderProgram.setInt("HEIGHT", HEIGHT);

            glBindVertexArray(VAO);
            glDrawArrays(GL_POINTS,0, NUMBER);

            glfwSwapBuffers(window);

            computeProgram.use();
            computeProgram.setInt("WIDTH", WIDTH);
            computeProgram.setInt("HEIGHT", HEIGHT);
            glBindVertexArray(VAO);
            glDispatchCompute(workGroup, 1, 1);

            decayShader.use();
            glDispatchCompute(WIDTH*HEIGHT/100, 1, 1);
            
            
        }

        
         //check calls and swap buffers
        glfwPollEvents();
    }
   
    glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, NULL, WIDTH* HEIGHT * sizeof(float), map);
    saveAsImg(map, WIDTH, HEIGHT, 0);
    
    glfwTerminate();
    return 0;
}