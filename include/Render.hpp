#ifndef RENDER_HPP
#define RENDER_HPP
// author: prisha sujin kumar
// desc: class to handle rendering and drawing

// third party libraries
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// std libraries
#include <vector>
#include <tuple>

// our libraries
#include "Geometry.hpp"
#include "Shader.hpp"
#include "Vertex.hpp"

class Render {
	public:

		/**
 		* @brief constructs a Render object
 		**/ 
		Render();

		/**
 		* @brief renders scene with objects
		* @param const glm::mat4& view, const glm::mat4& projection
 		**/ 
		void RenderScene(const glm::mat4& view, const glm::mat4& projection);

		/**
 		* @brief returns shader program
 		* @return GLuint
 		**/ 
    		GLuint GetShaderProgram() const;		
		
		
	private:
		// Geometry objects
		Geometry m_sphere;
		Geometry m_cube;
		
		// Vertex objects
		Vertex m_sphereVO;
		Vertex m_cubeVO;
		
		// Shader program
		GLuint m_shaderProgram;
};

#endif
