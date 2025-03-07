#ifndef LIGHTING_HPP
#define LIGHTING_HPP
// author: prisha sujin kumar
// desc: handles lighting and lighting gui 

// include statements
// third party libraries
#include <glm/glm.hpp>
// std libraries
#include <vector>

class Lighting {
	public:
		// struct for PointLight
		struct PointLight {
			bool enabled;
			glm::vec3 position;
			glm::vec3 color;
			float intensity;
		};

		// struct for DirectionalLight
		struct DirectionalLight {
			bool enabled;			
			glm::vec3 direction;
			glm::vec3 color;
		};

		// struct for SpotLight
		struct SpotLight {
			bool enabled;			
			glm::vec3 position;
			glm::vec3 direction;
			glm::vec3 color;
			float cutoff;
			float outerCutoff;
		};

		/**
 		* @brief constructs a Lightning object with PointLight, DirectionalLight, and SpotLight
 		**/ 
		Lighting();

		/**
 		* @brief applies lights
		* @param GLuint shaderProgram, const glm::vec3& viewPosition
 		**/ 
		void ApplyLights(GLuint shaderProgram, const glm::vec3& viewPosition);

		/**
 		* @brief renders lighting imgui controls
 		**/ 
		void RenderUI();

		// Lighting objects
		PointLight pointLight;
		DirectionalLight directionalLight;
		SpotLight spotLight;

	private:
		/**
 		* @brief handles point light imgui
 		**/ 
		void PointLightUI();

		/**
 		* @brief handles directional light imgui
 		**/ 
		void DirectionalLightUI();

		/**
 		* @brief handles spot light imgui
 		**/ 
		void SpotLightUI();
};


#endif // LIGHTING_HPP
