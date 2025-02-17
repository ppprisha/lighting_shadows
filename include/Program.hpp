#ifndef PROGRAM_HPP
#define PROGRAM_HPP

// class to setup input and setup of OpenGL and SDL

// -- include statements -- 
// third party libraries
#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif


// std libraries
#include <functional>

// our libraries
// -- end of include statements -- 

class Program {
	public:
		// constructor
		Program(int w, int h);
		// destructor
		~Program();
		// main program loop
		void SetLoopCallback(std::function<void(void)> callback);
		// get pointer to window
		SDL_Window* GetSDLWindow();
		void GetOpenGLVersionInfo();

	private:
		SDL_Window* m_window;
		SDL_GLContext m_openGLContext;
		unsigned int m_width;
		unsigned int m_height;
};

#endif
