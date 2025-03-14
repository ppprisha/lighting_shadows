#ifndef PROGRAM_HPP
#define PROGRAM_HPP
// author: prisha sujin kumar
// desc: class to setup input and setup of OpenGL and SDL

// third party libraries
#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

// std libraries
#include <functional>

// our libraries
#include "Camera.hpp"

class Program {
	public:
		/**
 		* @brief constructs a Program object
		* @param int w, int h
 		**/ 
		Program(int w, int h);
		
		/**
 		* @brief deallocates memory and cleans up
 		**/ 
		~Program();

		/**
		* @brief handles Camera and keyboard input
		* @param Camera& camera, float deltaTime
		**/
		void HandleCamera(Camera& camera, float deltaTime);

		/**
 		* @brief runs program through a loop
		* @param std::function<void(Camera&)> callback, Camera& camera)
 		**/ 
		void SetLoopCallback(std::function<void(Camera&)> callback, Camera& camera);
		
	
		/**
 		* @brief returns SDL_Window pointer
 		* @return SDL_Window*
 		**/ 
		SDL_Window* GetSDLWindow();

		/**
 		* @brief returns OpenGL info
 		**/ 
		void GetOpenGLVersionInfo();

	private:
		// initialization variables
		SDL_Window* m_window;
		SDL_GLContext m_openGLContext;
		unsigned int m_width;
		unsigned int m_height;
	
};

#endif
