#ifndef SHADER_H
#define SHADER_H

#include "../Common.h"

#include <iostream>
#include <fstream>
#include <sstream>


class Shader {

private:
	unsigned int shaderProgram;

public:
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
		std::ifstream vertexShaderStream;
		std::ifstream fragmentShaderStream;
		std::stringstream vertexShaderSource;
		std::stringstream fragmentShaderSource;


		vertexShaderStream.exceptions(std::ifstream::badbit | std::ifstream::failbit);
		fragmentShaderStream.exceptions(std::ifstream::badbit | std::ifstream::failbit);

		try {
			vertexShaderStream.open(vertexShaderPath);
			fragmentShaderStream.open(fragmentShaderPath);

			vertexShaderSource << vertexShaderStream.rdbuf();
			fragmentShaderSource << fragmentShaderStream.rdbuf();

			vertexShaderStream.close();
			fragmentShaderStream.close();
		}
		catch (std::ifstream::failure e) {
			std::cout << "Errore apertura shader source file" << std::endl;
			return;
		}

		std::string vertexShaderString = vertexShaderSource.str();
		const char* vShaderSource = vertexShaderString.c_str();

		std::string fragmentShaderString = fragmentShaderSource.str();
		const char* fShaderSource = fragmentShaderString.c_str();


		unsigned int vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vShaderSource, NULL);
		glCompileShader(vertexShader);

		CheckCompileErrors(vertexShader);

		unsigned int fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fShaderSource, NULL);
		glCompileShader(fragmentShader);

		CheckCompileErrors(fragmentShader);

		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

	}

	void CheckCompileErrors(unsigned int shader) {
		int  success;
		char infoLog[512];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

	}

	void Use() {
		glUseProgram(shaderProgram);
	}

	unsigned int GetShaderProgram() {
		return shaderProgram;
	}

	void SetInt(const char* uName, int value) {
		int location = glGetUniformLocation(shaderProgram, uName);
		glUniform1i(location, value);
	}

	void SetBool(const char* uName, bool value) {
		int location = glGetUniformLocation(shaderProgram, uName);
		glUniform1i(location, (int)value);
	}

	void SetFloat(const char* uName, float value) {
		int location = glGetUniformLocation(shaderProgram, uName);
		glUniform1f(location, value);
	}

	void SetVec3(const char* uName, glm::vec3 value) {
		int location = glGetUniformLocation(shaderProgram, uName);
		glUniform3fv(location, 1, glm::value_ptr(value));
	}

	void SetVec4(const char* uName, glm::vec4 value) {
		int location = glGetUniformLocation(shaderProgram, uName);
		glUniform4fv(location, 1, glm::value_ptr(value));
	}


	void SetMat4(const char* uName, glm::mat4 value) {
		int location = glGetUniformLocation(shaderProgram, uName);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

};


#endif