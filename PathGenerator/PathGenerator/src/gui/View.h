#pragma once
#include "element/Element.h"
#include <vector>

class View{

public:

	int depth, lastElementDepth = 0;
	GLFWwindow* window;
	std::vector<Element*> listElement;
	
	View(GLFWwindow* window) :window(window), depth(0) {}

	int addElement(Element* element) {

		element->depth = lastElementDepth;
		lastElementDepth++;
		listElement.push_back(element);

		return 0;

	}

	int handleInteraction(int cursorPosX, int cursorPosY) {

		Element* overedElement = nullptr;
		
		//if the cursor is over on of the element in the listElement
		for (int id = 0; id < listElement.size(); id++) {

			if (listElement[id]->type == SQUARE) {

				if (cursorPosX >= listElement[id]->x - (listElement[id]->width / 2) &&
					cursorPosX <= listElement[id]->x + (listElement[id]->width / 2) &&
					cursorPosY >= listElement[id]->y - (listElement[id]->height / 2) &&
					cursorPosY <= listElement[id]->y + (listElement[id]->height / 2)) {

					//check if the current element is smaller that overedElement
					if (overedElement == nullptr || listElement[id]->depth >= overedElement->depth) {
						overedElement = listElement[id];
					}
					
					
				}else {
					listElement[id]->resetColor();
				}
				
			}
			else if (listElement[id]->type == CIRCLE) {


				//check if the cursor is in a circle with the center in the element position and radius = element width
				if (sqrt(pow(cursorPosX - listElement[id]->x, 2) + pow(cursorPosY - listElement[id]->y, 2)) <= listElement[id]->width) {

					

					//check if the current element is smaller that overedElement
					if (overedElement == nullptr || listElement[id]->depth >= overedElement->depth) {
						overedElement = listElement[id];
					}
				}
				else {
					listElement[id]->resetColor();
				}

			}	
			
		}

		if (overedElement != nullptr) {

			//check if ther left mouse button is pressed
			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
				overedElement->onClick(cursorPosX, cursorPosY);
			}
			else {
				overedElement->onOver(cursorPosX, cursorPosY);
				
			}

		}
		
		
		return 0;
		
	};

	int drawElement(int height, int width) {

		for (int id = 0; id < listElement.size(); id++) {

			listElement[id]->drawElement(height, width);

		}
		
		return 0;
	}
};
