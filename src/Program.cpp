// author: prisha sujin kumar
// desc: class to handle sdl graphics program

// third party libraries
#include <glad/glad.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

// std libraries
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

// our libraries
#include "Program.hpp"
#include "Camera.hpp"

Program::Program(int w, int h) {
	m_window = NULL;
	m_width = w;
	m_height = h;

	// initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "ERROR (PROGRAM) - SDL could not initialize: " << SDL_GetError() << "\n";
		exit(EXIT_FAILURE);
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// double buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	// create window
	m_window = SDL_CreateWindow("Lighting and Shadow Engine",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			m_width,
			m_height,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	if (m_window == NULL) {
		std::cerr << "ERROR (PROGRAM) - Window could not be created: " << SDL_GetError() << "\n";
		exit(EXIT_FAILURE);
	}

	SDL_SetRelativeMouseMode(SDL_FALSE);
	SDL_CaptureMouse(SDL_TRUE);

	// create OpenGL context
	m_openGLContext = SDL_GL_CreateContext(m_window);
	if (!m_openGLContext) {
		std::cerr << "ERROR (PROGRAM) - OpenGL context could not be created: " << SDL_GetError() << "\n";
		exit(EXIT_FAILURE);
	}

	// initialize GLAD library
	if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
		std::cerr << "ERROR (PROGRAM) - Failed to initialize GLAD\n";
		exit(EXIT_FAILURE);
	}

	glViewport(0, 0, m_width, m_height);
	//std::cout << "viewport set to: " << m_width << "x" << m_height << std::endl;
	glDisable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	SDL_Log("SUCCESS! No errors during initialization\n\n");
	// SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN);
	GetOpenGLVersionInfo();

	// initialize dear imgui 
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); 
	(void)io;
	ImGui_ImplSDL2_InitForOpenGL(m_window, m_openGLContext);
	ImGui_ImplOpenGL3_Init("#version 410 core");

}

Program::~Program() {
	SDL_DestroyWindow(m_window);
	m_window = nullptr;
	SDL_Quit();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void Program::HandleCamera(Camera& camera, float deltaTime) {
	const Uint8* state = SDL_GetKeyboardState(NULL);


	if (state[SDL_SCANCODE_UP]) {
		camera.ProcessKeyboardRotation(0.0f, 1.0f, deltaTime);
	} if (state[SDL_SCANCODE_DOWN]) {
		camera.ProcessKeyboardRotation(0.0f, -1.0f, deltaTime);
	} if (state[SDL_SCANCODE_LEFT]) {
		camera.ProcessKeyboardRotation(-1.0f, 0.0f, deltaTime);
	} if (state[SDL_SCANCODE_RIGHT]) {
		camera.ProcessKeyboardRotation(1.0f, 0.0f, deltaTime);
	}
	
	camera.ProcessKeyboard(state, deltaTime);
	

}

void Program::SetLoopCallback(std::function<void(Camera&)> callback, Camera &mainCamera) {
	bool quit = false;
	SDL_Event e;
	SDL_WarpMouseInWindow(m_window, m_width/2, m_height/2);
    	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
	float lastFrame = SDL_GetTicks() / 1000.0f;
	

	while (!quit) {
		// dear imgui 
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
		float currentFrame = SDL_GetTicks() / 1000.0f;
		float deltaTime = currentFrame - lastFrame;		
		lastFrame = currentFrame;

		if (deltaTime > 0.1f) {
			deltaTime = 0.1f;
		}

		lastFrame = currentFrame;
		HandleCamera(mainCamera, deltaTime);

		while (SDL_PollEvent(&e) != 0) {
			ImGui_ImplSDL2_ProcessEvent(&e);
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			if (e.key.keysym.sym == SDLK_ESCAPE) {
                		quit = true;
            		} if (currentFrame - mainCamera.lastKey < mainCamera.doubleKey) { // back to original spot
				mainCamera.Reset();
				mainCamera.lastKey = -1.0f;
			}
		}

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		callback(mainCamera);

		// render imgui
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		SDL_GL_SwapWindow(GetSDLWindow());
		
	}

}

SDL_Window* Program::GetSDLWindow() {
	return m_window;
}

void Program::GetOpenGLVersionInfo() {
	SDL_Log("(Note: If you have two GPU's, make sure the correct one is selected)");
	SDL_Log("Vendor: %s",(const char*)glGetString(GL_VENDOR));
	SDL_Log("Renderer: %s",(const char*)glGetString(GL_RENDERER));
	SDL_Log("Version: %s",(const char*)glGetString(GL_VERSION));
	SDL_Log("Shading language: %s",(const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
}

