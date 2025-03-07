#ifndef SHADER_HPP
#define SHADER_HPP
// author: prisha sujin kumar
// desc: class to handle and load shaders

// third party libraries
#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif
#include <glad/glad.h>

// std libraries
#include <string>

class Shader {
	public:
		/**
 		* @brief loads shaders
		* @param const char * vertexShaderSource, const char * fragmentShaderSource
 		* @return GLuint
 		**/ 
		static GLuint LoadShaders(const char * vertexShaderSource, const char * fragmentShaderSource);
	private:
};

#endif
