#pragma once
class DrawableColor
{
	float red, green, blue;

public:
	DrawableColor(float red, float green, float blue) : red(red), green(green), blue(blue) {}

	void setRed(float red) { this->red = red; }
	void setGreen(float green) { this->green = green; }
	void setBlue(float blue) { this->blue = blue; }

	float getRed() const { return red; }
	float getGreen() const { return green; }
	float getBlue() const { return blue; }

};