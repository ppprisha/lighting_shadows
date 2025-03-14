// author: prisha sujin kumar
// desc: class for main execution

// third party libraries
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// std libraries
#include <iostream>

// our libraries
#include "Camera.hpp"
#include "Program.hpp"
#include "Render.hpp"
#include "Lighting.hpp"

int main(int argc, char** argv) {
	Program myProgram(1600, 900);
    	Render myRenderer;
    	Camera mainCamera;
	Lighting lighting;
    
    	myProgram.SetLoopCallback([&](Camera& camera) { 	
        	glm::mat4 projection = camera.GetProjectionMatrix(1600.0f/900.0f);
        	glm::mat4 view = camera.GetViewMatrix();

	
		lighting.RenderUI();
		lighting.ApplyLights(myRenderer.GetShaderProgram(), camera.Position);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
		myRenderer.RenderScene(view, projection);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);}, mainCamera);
	
	return 0;
}
