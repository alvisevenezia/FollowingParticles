#include "DrawableShape.h"

class Square : public DrawableShape
{

public:
	Square(int x, int y, int height, int width, DrawableColor color, GLFWwindow* window);
	

	int initialize() override;

	int drawShape(int width, int height) override;

};

