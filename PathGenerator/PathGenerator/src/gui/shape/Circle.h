#pragma once
#include "DrawableShape.h"

class Circle : public DrawableShape {

public:

	Circle(int x, int y, int height, int width, DrawableColor color, GLFWwindow* window) : DrawableShape(x, y, height, width, color, window) {}

	int initialize() {

		program = new Shader("./shaders/square_vertex_shader.glsl", "./shaders/square_fragment_shader.glsl");

		int numOfTrianle = 64;

		//generate vertices for a cirlce of diameter height made of 64 triangles
		size_t size = (numOfTrianle + 1) * 3 * sizeof(float);
		float* vertices = (float*)malloc(size);

		for (int id = 0; id < numOfTrianle; id++) {

			float angle = 2 * 3.14159 * id / numOfTrianle;
			float x = this->x + height * cos(angle);
			float y = this->y + height * sin(angle);

			vertices[id * 3] = x;
			vertices[id * 3 + 1] = y;
			vertices[id * 3 + 2] = 0.0f;

			std::cout << "Verticies " << id << " " << x << " " << y << " 0" << std::endl;

		}

		vertices[numOfTrianle * 3] = x;
		vertices[numOfTrianle * 3+1] = y;
		vertices[numOfTrianle * 3+2] = 0.0f;
		
		std::cout << "Verticies 13 "<< x << " " << y << " 0" << std::endl;

		//set up the indices for the button follwing the pattern {0,1,2,0,2,3,0,3,4}
		unsigned int* indices = (unsigned int*)malloc(sizeof(unsigned int) * numOfTrianle * 3);

		for (int id = 0; id < numOfTrianle-1; id++) {

			indices[id * 3] = 12;
			indices[id * 3 + 1] = id;
			indices[id * 3 + 2] = id + 1;

		}

		indices[(numOfTrianle - 1) * 3] = 12;
		indices[(numOfTrianle - 1) * 3 + 1] = numOfTrianle - 1;
		indices[(numOfTrianle - 1) * 3 + 2] = 0;

		// Set up vertex buffer object
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

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
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*numOfTrianle*3, indices, GL_STATIC_DRAW);

		this->ebo = ebo;
		this->vao = vao;
		this->vbo = vbo;
		return 0;
	}

	int drawShape(int width, int height) {

		program->use();
		program->setInt("WIDTH", width);
		program->setInt("HEIGHT", height);
		program->set4Float("color", color.getRed(), color.getGreen(), color.getBlue(), 1.0f);

		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLE_STRIP, 64*3, GL_UNSIGNED_INT, 0);

		return 0;

	}
};