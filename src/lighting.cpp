// author: prisha sujin kumar
// desc: handles lighting and lighting gui

// third party libraries
#include <imgui.h>
#include <glad/glad.h>

// std libraries
#include <iostream>
#include <locale>

// our libraries
#include "Lighting.hpp"

Lighting::Lighting() {
	pointLight = PointLight {
		true,
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 0.6f),
		1.5f
	};

	directionalLight = DirectionalLight {
		true,
		glm::vec3(-0.2f, -1.0f, -0.3f),
		glm::vec3(1.0f, 0.4f, 0.8f)
	};

	spotLight = SpotLight {
		true,
		glm::vec3(0.0f, 3.0f, 3.0f),
		glm::vec3(0.0f, -1.0f, 0.0f),
		glm::vec3(0.8f, 0.2f, 0.6f),
		12.5f,
		17.5f
	};
}

void Lighting::ApplyLights(GLuint shaderProgram, const glm::vec3& viewPosition) {
	glUseProgram(shaderProgram);

	auto CheckUniform = [](GLint loc, const char* name) {
		if (loc == -1) {
			std::cerr << "missing uniform: " << name << std::endl;
		}
	};



	GLint loc = glGetUniformLocation(shaderProgram, "pointLight.enabled");
	CheckUniform(loc, "pointLight.enabled");
	glUniform1i(loc, pointLight.enabled);
	if (pointLight.enabled) {
		GLint positionLoc = glGetUniformLocation(shaderProgram, "pointLight.position");
		GLint colorLoc = glGetUniformLocation(shaderProgram, "pointLight.color");
		GLint intensityLoc = glGetUniformLocation(shaderProgram, "pointLight.intensity");

		glUniform3fv(positionLoc, 1, &pointLight.position[0]);
		glUniform3fv(colorLoc, 1, &pointLight.color[0]);
		glUniform1f(intensityLoc, pointLight.intensity);
	}

	loc = glGetUniformLocation(shaderProgram, "directionalLight.enabled");	
	CheckUniform(loc, "directionalLight.enabled");
	glUniform1i(loc, directionalLight.enabled);
	if (directionalLight.enabled) {
		GLint directionLoc = glGetUniformLocation(shaderProgram, "directionalLight.direction");
		GLint colorLoc = glGetUniformLocation(shaderProgram, "directionalLight.color");

		glUniform3fv(directionLoc, 1, &directionalLight.direction[0]);
		glUniform3fv(colorLoc, 1, &directionalLight.color[0]);
	}

	loc = glGetUniformLocation(shaderProgram, "spotLight.enabled");
	CheckUniform(loc, "spotLight.enabled");
	glUniform1i(loc, spotLight.enabled);
	if (spotLight.enabled) {
		GLint positionLoc = glGetUniformLocation(shaderProgram, "spotLight.position");
		GLint directionLoc = glGetUniformLocation(shaderProgram, "spotLight.direction");
		GLint colorLoc = glGetUniformLocation(shaderProgram, "spotLight.color");
		GLint cutoffLoc = glGetUniformLocation(shaderProgram, "spotLight.cutoff");
		GLint outerCutoffLoc = glGetUniformLocation(shaderProgram, "spotLight.outerCutoff");

		glUniform3fv(positionLoc, 1, &spotLight.position[0]);
		glUniform3fv(directionLoc, 1, &spotLight.direction[0]);
		glUniform3fv(colorLoc, 1, &spotLight.color[0]);
		glUniform1f(cutoffLoc, cos(glm::radians(spotLight.cutoff)));
		glUniform1f(outerCutoffLoc, cos(glm::radians(spotLight.outerCutoff)));


	}

	GLint viewPositionLoc = glGetUniformLocation(shaderProgram, "viewPosition");
	glUniform3fv(viewPositionLoc, 1, &viewPosition[0]);
}

void Lighting::RenderUI() {
	ImGui::Begin("Lighting Controls");

	ImGui::Checkbox("Point Light", &pointLight.enabled);
	if (pointLight.enabled) {
		PointLightUI();
	} 

	ImGui::Checkbox("Directional Light", &directionalLight.enabled);
	if (directionalLight.enabled) {
		DirectionalLightUI();
	}

	ImGui::Checkbox("Spotlight", &spotLight.enabled);
	if (spotLight.enabled) {
		SpotLightUI();
	}

	ImGui::End();
}

void Lighting::PointLightUI() {
	ImGui::SliderFloat3("Position##Point", &pointLight.position[0], -5.0f, 5.0f);
	ImGui::ColorEdit3("Color##Point", &pointLight.color[0]);
	ImGui::SliderFloat("Intensity##Point", &pointLight.intensity, 0.0f, 2.0f);
}

void Lighting::DirectionalLightUI() {
	ImGui::SliderFloat3("Directional##Directional", &directionalLight.direction[0], -1.0f, 1.0f);
	ImGui::ColorEdit3("Color##Directional", &directionalLight.color[0]);
}

void Lighting::SpotLightUI() {
	ImGui::SliderFloat3("Position##Spot", &spotLight.position[0], -5.0f, 5.0f);
	ImGui::SliderFloat3("Direction##Spot", &spotLight.direction[0], -1.0f, 1.0f);
	ImGui::ColorEdit3("Color##Spot", &spotLight.color[0]);
	ImGui::SliderFloat("Cutoff##Spot", &spotLight.cutoff, 0.0f, 45.0f);
	ImGui::SliderFloat("Outer Cutoff##Spot", &spotLight.outerCutoff, 0.0f, 45.0f);
}




