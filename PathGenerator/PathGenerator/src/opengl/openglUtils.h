#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void MessageCallback(GLenum source,GLenum type,GLuint id, GLenum severity,GLsizei length,const GLchar* message, const void* userParam);

void processInput(GLFWwindow* window);

GLFWwindow* initGLProcess(int majorVersion,int minorVersion, int width, int height);