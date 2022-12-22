#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../../utils/shader.h"
#include "../DrawableColor.h"

class DrawableShape
{
	
public:

	int x, y, height, width;
	DrawableColor color;
	GLuint vbo;
	GLuint vao;
	GLuint ebo;
	Shader* program;
	GLFWwindow* window;
	
	DrawableShape(int x, int y, int height, int width, DrawableColor color, GLFWwindow* window);

	int virtual drawShape(int width, int height);

	int virtual initialize();
};

