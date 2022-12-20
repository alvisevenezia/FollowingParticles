#include <glad/glad.h>
#include <GLFW/glfw3.h>

class DrawableColor
{
	int red, green, blue;

public:
	DrawableColor(int red, int green, int blue) : red(red), green(green), blue(blue) {}

	void setRed(int red) { this->red = red; }
	void setGreen(int green) { this->green = green; }
	void setBlue(int blue) { this->blue = blue; }

	int getRed() const { return red; }
	int getGreen() const { return green; }
	int getBlue() const { return blue; }
};

class DrawableShape
{

public:

	int x, y, height, width;
	DrawableColor color;
	DrawableShape* next;
	DrawableShape* previous;
	
	DrawableShape(int x, int y, int height, int width, DrawableColor color);

	~DrawableShape();

	int virtual drawShape();
};

class Square : DrawableShape{

	Square(int x, int y, int height, int width, DrawableColor color);
	
	~Square();

	int drawShape();
};
