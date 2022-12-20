#include "DrawableShape.h"
#include <iostream>

DrawableShape::DrawableShape(int x, int y, int height, int width, DrawableColor color) : x(x), y(y), height(height), width(width), color(color), next(nullptr), previous(nullptr) {}

DrawableShape::~DrawableShape() {

	delete next;
	delete previous;
	delete this;
}

int DrawableShape::drawShape() {

	std::cout << "function drawShape not defined"<< std::endl;

	return 0;
	
}

Square::Square(int x, int y, int height, int width, DrawableColor color) : DrawableShape(x, y, height, width, color) {}

Square::~Square(){

	delete this;
}
	
int Square::drawShape() {

	std::cout << "drawing square" << std::endl;
	
	//array of verticies relative to the center of the square and the specified width and height
	float vertices[] = {
		// positions          // colors
		-width / 2.0f,  height / 2.0f, 0.0f,  // top left
		width / 2.0f,  height / 2.0f, 0.0f,  // top right
		width / 2.0f, -height / 2.0f, 0.0f,  // bottom right
		-width / 2.0f, -height / 2.0f, 0.0f   // bottom left
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first Triangle
		1, 2, 3    // second Triangle
	};
	
	return 0;
}