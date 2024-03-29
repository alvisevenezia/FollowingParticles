#pragma once
#include "Element.h"
#include "../shape/Square.h"

class Button : public Element {

public:
	
	Button(int x, int y, int height, int width, DrawableColor color,GLFWwindow* window, ShapeType type = SQUARE) : Element(x, y, height, width, color,type) {
	
		if (type == CIRCLE) {
			DrawableShape* circle = new Circle(x, y, height, width, color, window);
			circle->initialize();
			addShape(circle);
		}
		else if(type == SQUARE){

			Square* square = new Square(x, y, height, width, color, window);
			square->initialize();
			addShape(square);

		}
	
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