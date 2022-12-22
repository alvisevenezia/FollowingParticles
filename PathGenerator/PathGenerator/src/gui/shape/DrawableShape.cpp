#include "DrawableShape.h"
#include <iostream>

DrawableShape::DrawableShape(int x, int y, int height, int width, DrawableColor color,GLFWwindow* window) : x(x), y(y), height(height), width(width), color(color),window(window){}

int DrawableShape::drawShape(int width, int height) {

	std::cout << "function drawShape not defined"<< std::endl;

	return 0;
	
}

int DrawableShape::initialize() {

	std::cout << "function initiliaze not defined" << std::endl;

	return 0;
	
}