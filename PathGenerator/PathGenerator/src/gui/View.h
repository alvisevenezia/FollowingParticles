#pragma once
#include "element/Element.h"

class View{

	int depth;
	GLFWwindow* window;
	std::priority_queue<Element> listElement;

	View(GLFWwindow* window);

	int handleInteraction();

	int drawElement();
};
