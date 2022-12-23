#pragma once
#include "Element.h"
#include "../shape/Square.h"

class Button : public Element {

public:
	
	Button(int x, int y, int height, int width, DrawableColor color,GLFWwindow* window) : Element(x, y, height, width, color) {
	
		Square* baseShape = new Square(x, y, height, width, color, window);
		baseShape->initialize();
		addShape(baseShape);
	
	}
	
	int onClick(int cursorPosX, int cursorPosY) override {

		for (DrawableShape* shape : shapeList) {

			shape->color = clickColor;

		}
		return 0;
	}

	
	int onOver(int cursorPosX,int cursorPosY) override {
		
		for (DrawableShape* shape : shapeList) {

			shape->color = overColor;

		}
		return 0;
	}

	
	
};