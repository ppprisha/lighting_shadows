#ifndef SHADER_HPP
#define SHADER_HPP

// class to handle and load shaders

// -- include statements --
// third party libraries
#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif
#include <glad/glad.h>
// std libraries
#include <string>
// our libraries
// -- end of include statements -- 

class Shader {
	public:
		GLuint LoadShaders(const char * vertexShaderSource, const char * fragmentShaderSource);
	private:
};

#endif
