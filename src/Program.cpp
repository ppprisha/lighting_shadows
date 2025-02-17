// author: prisha sujin kumar
// class to handle sdl graphics program

// -- include statements -- 
// third party libraries
#include <glad/glad.h>

// std libraries
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

// our libraries
#include "Program.hpp"
// -- end of include statements -- 

// constructor and initialization
Program::Program(int w, int h) {
	m_window = NULL;
	m_width = w;
	m_height = h;

	// initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "ERROR (SDL) - SDL could not initialize: " << SDL_GetError() << "\n";
		exit(EXIT_FAILURE);
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// double buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	// create window
	m_window = SDL_CreateWindow("Lighting and Shadow",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			m_width,
			m_height,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	if (m_window == NULL) {
		std::cerr << "ERROR (SDL) - Window could not be created: " << SDL_GetError() << "\n";
		exit(EXIT_FAILURE);
	}

	// create OpenGL context
	m_openGLContext = SDL_GL_CreateContext(m_window);
	if (m_openGLContext == NULL) {
		std::cerr << "ERROR (SDL) - OpenGL context could not be created: " << SDL_GetError() << "\n";
		exit(EXIT_FAILURE);
	}

	// initialize GLAD library
	if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
		std::cerr << "ERROR (SDL) - Failed to initialize GLAD\n";
		exit(EXIT_FAILURE);
	}

	SDL_Log("No errors during initialization\n\n");
	// SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN); // uncomment if needed
	GetOpenGLVersionInfo();
}

// destructor
Program::~Program() {
	SDL_DestroyWindow(m_window);
	m_window = nullptr;
	SDL_Quit();
}

// program run
void Program::SetLoopCallback(std::function<void(void)> callback) {
	bool quit = false;
	SDL_Event e;
	SDL_WarpMouseInWindow(m_window, m_width/2, m_height/2);
    	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);	

	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}
		SDL_Delay(25);
		SDL_GL_SwapWindow(GetSDLWindow());
	}

}

// get pointer to window
SDL_Window* Program::GetSDLWindow() {
	return m_window;
}

// get OpenGL info
void Program::GetOpenGLVersionInfo() {
	SDL_Log("(Note: If you have two GPU's, make sure the correct one is selected)");
	SDL_Log("Vendor: %s",(const char*)glGetString(GL_VENDOR));
	SDL_Log("Renderer: %s",(const char*)glGetString(GL_RENDERER));
	SDL_Log("Version: %s",(const char*)glGetString(GL_VERSION));
	SDL_Log("Shading language: %s",(const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
}

