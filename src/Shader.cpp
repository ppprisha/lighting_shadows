// author: prisha sujin kumar
// class to handle and load shaders

// -- include statements -- 
// third party libraries
// std libraries
#include <iostream>
#include <fstream>
// our libraries
// -- end of include statements --

GLuint Shader::LoadShaders(const char * vertexShaderSource, const char * fragmentShaderSource) {
	using namespace std;
	GLuint myVertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint myFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// read vertex shader
	string vertexShaderCode;
	ifstream VertexShaderStream(vertexShaderSource, std::ios::in);
	if(VertexShaderStream.is_open()) {
		stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	} else {
		printf("ERROR (SHADERS) - Unable to read vertex shader\n");
		getchar();
		return 0;
	}

	// read fragment shader
	string fragmentShaderCode;
	ifstream FragmentShaderStream(vertexShaderSource, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		fragmentShaderCode = sstr.str();
		fragmentShaderStream.close();
	} else {
		printf("ERROR (SHADERS) - Unable to read fragment shader\n");
		getchar();
		return 0;
	}

	GLint result = GL_FALSE;
	int infoLogLength;

	// compile vertex shader
	printf("Compiling shader: %s\n", vertexShaderSource);
	char const * vertexSourcePointer = vertexShaderCode.c_str();
	glShaderSource(vertexShaderSource, 1, &vertexSourcePointer, NULL);
	glCompileShader(vertexShaderSource);

	glGetShaderiv(vertexShaderSource, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertexShaderSource, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		vector<char> vertexShaderErrorMessage(infoLogLength+1);
		glGetShaderInfoLog(vertexShaderSource, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
		printf("%s\n", &vertexShaderErrorMessage[0]);
	}

	// compile fragment shader
	printf("Compiling shader: %s\n", fragmentShaderSource);
	char const * fragmentSourcePointer = fragmentShaderCode.c_str();
	glShaderSource(fragmentShaderSource, 1, &fragmentSourcePointer, NULL);
	glCompileShader(fragmentShaderSource);

	glGetShaderiv(fragmentShaderSource, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragmentShaderSource, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		vector<char> fragmentShaderErrorMessage(infoLogLength+1);
		glGetShaderInfoLog(fragmentShaderSource, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);
		printf("%s\n", &fragmentShaderSourceMessage[0]);
	}

	// link programs 
	printf("Linking programs...\n");
	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderSource);
	glAttachShader(programID, fragmentShaderSource);
	glLinkProgram(programID);

	// check programs
	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		vector<char> programErrorMessage(infoLogLength+1);
		glGetProgramInfoLog(programID, infoLogLength, NULL, &programErrorMessage[0]);
		printf("%s\n", &programErrorMessage[0]);
	}

	glDetachShader(programID, vertexShaderSource);
	glDetachShader(programID, fragmentShaderSource);

	glDeleteShader(vertexShaderSource);
	glDeleteShader(fragmentShaderSource);

	return programID;
}


