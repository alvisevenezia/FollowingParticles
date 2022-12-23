#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../../utils/shader.h"
#include "../DrawableColor.h"

enum ShapeType {
	SQUARE,
	CIRCLE,
	TRIANGLE,
	LINE,
	TEXT
};

class DrawableShape
{
	
public:

	

	int x, y, height, width;
	DrawableColor color;
	GLuint vbo;
	GLuint vao;
	GLuint ebo;
	Shader* program;
	GLFWwindow* window;
	
	DrawableShape(int x, int y, int height, int width, DrawableColor color, GLFWwindow* window) : x(x), y(y), height(height), width(width), color(color), window(window){
	
		vbo = -1;
		vao = -1;
		ebo = -1;
		program = nullptr;
	}

	int virtual drawShape(int width, int height) {

		return 0;

	}

	int virtual initialize() {

		return 0;

	}

};

