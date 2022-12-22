#include "Square.h"

Square::Square(int x, int y, int height, int width, DrawableColor color, GLFWwindow* window) : DrawableShape(x, y, height, width, color,window) {}

int Square::initialize(){

	program = new Shader("./shaders/square_vertex_shader.glsl", "./shaders/square_fragment_shader.glsl");
	
	// Set up vertex data for the button
	float vertices[] = {
		// x, y, z, u, v
		x - (width / 2) ,y - (height / 2), 0.0f,
		x - (width / 2), y + (height / 2), 0.0f,
		x + (width / 2), y - (height / 2), 0.0f,
		x + (width / 2), y + (height / 2), 0.0f,
	};

	//set up the indices for the button
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 1
	};

	// Set up vertex buffer object
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Set up vertex array object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);

	// Set up vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// Set up element array buffer
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	this->ebo = ebo;
	this->vao = vao;
	this->vbo = vbo;
	return 0;
}

int Square::drawShape(int width,int height) {

	//check if the mosue is over the button

	program->use();
	program->setInt("WIDTH", width);
	program->setInt("HEIGHT", height);

	//variable for the crusor coord
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	std::cout << "X: " << xpos << " Y: " << ypos << std::endl;
	
	//check if the cursor is over the button
	if (xpos > x - (this->width / 2) && xpos < x + (this->width / 2) && ypos > y - (this->height / 2) && ypos < y + (this->height / 2)) {
		program->set4Float("color", 0.0f, 1.0f, 0.0f,1.0f);
		
		std::cout << "Mouse is over the button" << std::endl;
	}
	else {
		program->set4Float("color", color.getRed(), color.getGreen(), color.getBlue(),1.0f);
	}
	
	
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	return 0;

}