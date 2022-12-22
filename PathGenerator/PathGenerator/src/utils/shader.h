#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {

public:

	unsigned int ID;

	Shader(const char* computePath) {

		std::string computeCode;
		std::ifstream cShaderFile;

		cShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {

			cShaderFile.open(computePath);
			std::stringstream cShaderStream;

			cShaderStream << cShaderFile.rdbuf();
			cShaderFile.close();

			computeCode = cShaderStream.str();

		}
		catch (std::ifstream::failure e) {
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}

		const char* cShaderCode = computeCode.c_str();

		//compile shader
		unsigned int compute;
		GLint success;
		char infoLog[512];

		compute = glCreateShader(GL_COMPUTE_SHADER);
		glShaderSource(compute, 1, &cShaderCode, NULL);
		glCompileShader(compute);
		glGetShaderiv(compute, GL_COMPILE_STATUS, &success);

		if (!success) {

			glGetShaderInfoLog(compute, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPUTE::COMPILATION_FAILED\n" << infoLog << std::endl;

		}

		ID = glCreateProgram();
		glAttachShader(ID, compute);
		glLinkProgram(ID);
		glGetProgramiv(ID, GL_LINK_STATUS, &success);

		if (!success) {

			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "ERROR::COMPUTE_PROGRAMM::LINKING_FAILED\n" << infoLog << std::endl;

		}

		glDeleteShader(compute);

	}

	Shader(const char* vertexPath, const char* fragmentPath) {

		//load source code from files
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {

			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
				
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e) {
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}

		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		//compile shaders
		unsigned int vertex,fragment;
		int succes;
		char infoLog[512];

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &succes);

		if (!succes) {

			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

		}

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode,NULL);
		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &succes);

		if (!succes) {

			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;

		}

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		glGetProgramiv(ID, GL_LINK_STATUS, &succes);

		if (!succes) {

			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;

		}

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	void use() {

		glUseProgram(ID);

	}

	void setBool(const std::string& name, bool value)const {

		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);

	}
	void setInt(const std::string& name, int value)const {

		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);

	}
	void setFloat(const std::string& name, float value)const {

		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);

	}

	void set4Float(const std::string& name, float v1,float v2,float v3, float v4)const {

		glUniform4f(glGetUniformLocation(ID, name.c_str()), v1,v2,v3,v4);

	}
};

#endif // DEBUG
