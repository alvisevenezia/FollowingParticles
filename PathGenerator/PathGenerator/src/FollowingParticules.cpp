// PathGenerator.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "utils/shader.h"
#include "utils/track.h"
#include "utils/spawnUtils.h"
#include "opengl/openglUtils.h"
#include "gui/shape/Square.h"

#define WIDTH 1920
#define HEIGHT 1080
#define FRAME_RATE 120
#define NUMBER 1024*1024*3
#define WORK_GROUP_SIZE 1024


int main()
{
  
	GLFWwindow* window = initGLProcess(4, 3,WIDTH,HEIGHT);

    assert(window != nullptr);

    Shader shaderProgram("./shaders/basic_vertex_shader.glsl", "./shaders/fragment_shader.glsl");
    Shader computeProgram("./shaders/compute_shader.glsl");
    Shader decayShader("./shaders/map_update_shader.glsl");
    Shader program = Shader("./shaders/square_vertex_shader.glsl", "./shaders/square_fragment_shader.glsl");
	
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
    
    DrawableColor squareColor(0.2, 0.2, 1.0);

	Square square(WIDTH/2, HEIGHT/2, 250, 500,squareColor,window);
    square.initialize();
    
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
            
            
			square.drawShape(WIDTH,HEIGHT);
            
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