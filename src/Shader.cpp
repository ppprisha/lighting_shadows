// author: prisha sujin kumar
// desc: class to handle and load shaders

// third party libraries
#include <glad/glad.h>

// std libraries
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

// our libraries
#include "Shader.hpp"

GLuint Shader::LoadShaders(const char * vertexShaderSource, const char * fragmentShaderSource) {
	GLuint myVertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint myFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// read vertex shader
	std::string vertexShaderCode;
	std::ifstream VertexShaderStream(vertexShaderSource, std::ios::in);
	if(VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		vertexShaderCode = sstr.str();
		VertexShaderStream.close();
	} else {
		std::cerr << "ERROR (SHADER) - unable to read vertex shader\n";
		getchar();
		return 0;
	}

	// read fragment shader
	std::string fragmentShaderCode;
	std::ifstream fragmentShaderStream(fragmentShaderSource, std::ios::in);
	if (fragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << fragmentShaderStream.rdbuf();
		fragmentShaderCode = sstr.str();
		fragmentShaderStream.close();
	} else {
		std::cerr << "ERROR (SHADER) - unable to read fragment shader\n";
		getchar();
		return 0;
	}

	GLint result = GL_FALSE;
	int infoLogLength;

	// compile vertex shader
	printf("Compiling shader... %s\n", vertexShaderSource);
	char const * vertexSourcePointer = vertexShaderCode.c_str();
	glShaderSource(myVertexShader, 1, &vertexSourcePointer, NULL);
	glCompileShader(myVertexShader);

	glGetShaderiv(myVertexShader, GL_COMPILE_STATUS, &result);
    	glGetShaderiv(myVertexShader, GL_INFO_LOG_LENGTH, &infoLogLength);	
	if (infoLogLength > 0) {
		std::vector<char> vertexShaderErrorMessage(infoLogLength+1);
		glGetShaderInfoLog(myVertexShader, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
		printf("%s\n", &vertexShaderErrorMessage[0]);
	}

	// compile fragment shader
	printf("Compiling shader... %s\n", fragmentShaderSource);
	char const * fragmentSourcePointer = fragmentShaderCode.c_str();
	glShaderSource(myFragmentShader, 1, &fragmentSourcePointer, NULL);
	glCompileShader(myFragmentShader);

	glGetShaderiv(myFragmentShader, GL_COMPILE_STATUS, &result);
    	glGetShaderiv(myFragmentShader, GL_INFO_LOG_LENGTH, &infoLogLength);	
	if (infoLogLength > 0) {
		std::vector<char> fragmentShaderErrorMessage(infoLogLength+1);
		glGetShaderInfoLog(myFragmentShader, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);
		printf("%s\n", &fragmentShaderErrorMessage[0]);
	}

	// link programs 
	printf("Linking programs...\n");
	GLuint programID = glCreateProgram();
	glAttachShader(programID, myVertexShader);
	glAttachShader(programID, myFragmentShader);
	glLinkProgram(programID);

	GLint linkStatus;
	glGetProgramiv(programID, GL_LINK_STATUS, &linkStatus);
	if (linkStatus == GL_FALSE) {
    		GLint infoLogLength;
    		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    
    		std::vector<GLchar> infoLog(infoLogLength + 1);
    		glGetProgramInfoLog(programID, infoLogLength, NULL, &infoLog[0]);
    
    		std::cerr << "ERROR (SHADER) - shader program linking failed: \n" << &infoLog[0] << std::endl;
    
    		glDeleteProgram(programID);
    		return 0;
	}
	
	GLint isLinked = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, &isLinked);
	
	if (isLinked == GL_FALSE) {
		GLint maxLength = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);
    		std::vector<GLchar> infoLog(maxLength);
    		glGetProgramInfoLog(programID, maxLength, &maxLength, &infoLog[0]);
    		std::cerr << "ERROR (SHADERS) - shader program linking failed:\n" << infoLog.data() << std::endl;
	}

	// check programs
	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		std::vector<char> programErrorMessage(infoLogLength+1);
		glGetProgramInfoLog(programID, infoLogLength, NULL, &programErrorMessage[0]);
		printf("%s\n", &programErrorMessage[0]);
	}

	glDetachShader(programID, myVertexShader);
	glDetachShader(programID, myFragmentShader);
	glDeleteShader(myVertexShader);
	glDeleteShader(myFragmentShader);

	return programID;
}


