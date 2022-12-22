#pragma once
#include "../DrawableColor.h"
#include "../shape/DrawableShape.h"
#include "../controler/Controler.h"
#include "../../utils/Compare.h"
#include <queue>
#include <vector>

class Element {

	
public:

	int x, y, height, width;
	int priority, depth;
	DrawableColor color;
	std::vector<DrawableShape> shapeList;
	std::vector<Element> children;
	
	Element(int x, int y, int height, int width);

	~Element();

	int setControler(Controler* controler);
	
	int addShape(DrawableShape shape);

	int removeShape(DrawableShape shape);

	int addElement(Element element);
	
	int removeElement(Element element);

	int drawElement();

	int resizeElement(int width, int height);

	int moveElement(int x, int y);
};