// PathGenerator.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "utils/shader.h"
#include "utils/track.h"
#include "utils/spawnUtils.h"
#include "opengl/openglUtils.h"

#define WIDTH 1920
#define HEIGHT 1080
#define FRAME_RATE 120
#define NUMBER 1024*1024*3
#define WORK_GROUP_SIZE 1024


int main()
{

    float vertices[] = {
		// positions          // colors
		200,  200, 0.0f,  // top left
		 200,  1000, 0.0f,  // top right
		 1000, 200, 0.0f,  // bottom right
		1000, 1000, 0.0f   // bottom left
	};

    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first Triangle
        1, 2, 3    // second Triangle
    };
  
	GLFWwindow* window = initGLProcess(4, 3,WIDTH,HEIGHT);

    assert(window != nullptr);

    Shader shaderProgram("./shaders/basic_vertex_shader.glsl", "./shaders/fragment_shader.glsl");
    Shader computeProgram("./shaders/compute_shader.glsl");
    Shader decayShader("./shaders/map_update_shader.glsl");
	
    int workGroup = NUMBER/WORK_GROUP_SIZE;
    float* particles = (float*)calloc(NUMBER * 3, sizeof(float));
    float* map = (float*)calloc(WIDTH * HEIGHT,sizeof(float));

    srand(time(NULL));
    spawnParticle(particles, middle_in_circle, NUMBER,HEIGHT,WIDTH);


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
            glBindVertexArray(VAO);
            glDrawArrays(GL_POINTS,0, NUMBER);

            glfwSwapBuffers(window);
            
            computeProgram.use();
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