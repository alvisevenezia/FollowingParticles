#pragma once
#include "../DrawableColor.h"
#include "../shape/DrawableShape.h"
#include <vector>

class Element {

	
public:

	int x, y, height, width;
	int priority, depth;
	ShapeType type;
	DrawableColor baseColor,overColor,clickColor,currentColor;
	std::vector<DrawableShape*> shapeList;
	std::vector<Element> children;
	
	Element(int x, int y, int height, int width, DrawableColor baseColor,ShapeType type = SQUARE) :x(x), y(y), height(height), width(width), depth(0), priority(0), baseColor(baseColor), overColor(baseColor), clickColor(baseColor),currentColor(baseColor){
		this->type = type;
	}
	virtual ~Element(){}

	int setBaseColor(DrawableColor baseColor) {

		this->baseColor = baseColor;
		return 0;
	}

	int setOverColor(DrawableColor overColor) {

		this->overColor = overColor;
		return 0;
	}

	int setClickColor(DrawableColor clickColor) {

		this->clickColor = clickColor;
		return 0;
	}

	int addShape(DrawableShape* shape) {

		shapeList.push_back(shape);
		return 0;

	}

	int drawElement(int height, int width) {

		for (DrawableShape* shape : shapeList) {
			shape->drawShape(width, height);
		}

		for (int id = 0; id < children.size(); id++) {
			children[id].drawElement(width, height);
		}
		
		return 0;

	}

	int resizeElement(int width, int height) {

		this->width = width;
		this->height = height;
		
		for (int id = 0; id < children.size(); id++) {
			children[id].resizeElement(std::min(width, children[id].width), std::min(height, children[id].height));
		}

	}

	int moveElement(int x, int y) {

		this->x = x;
		this->y = y;

	}

	virtual int onClick(int cursorPosX, int cursorPosY) = 0;

	virtual int onOver(int cursorPosX, int cursorPosY) = 0;

	int resetColor() {

		for (DrawableShape* shape : shapeList) {
			shape->color = baseColor;
		}

		for (int id = 0; id < children.size(); id++) {
			children[id].resetColor();
		}

		return 0;
	}
};