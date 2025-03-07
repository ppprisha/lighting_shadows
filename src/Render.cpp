// author: prisha sujin kumar
// desc: class to handle rendering and drawing

// third party libraries
// std libraries
#include <iostream>

// our libraries
#include "Render.hpp"

Render::Render() {
	// create sphere
	m_sphere.GenerateSphere(0.5f, 36, 18);
	float *sphereData = m_sphere.GetBufferDataPtr();
	unsigned int sphereVCount = m_sphere.GetBufferDataSize() / 14;
	m_sphereVO.CreateNormalBufferLayout(sphereVCount, m_sphere.GetIndicesSize(), 
			sphereData, m_sphere.GetIndicesDataPtr());

	// create cube
	m_cube.GenerateCube(1.0f);
	float *cubeData = m_cube.GetBufferDataPtr();
	unsigned int cubeVCount = m_cube.GetBufferDataSize() / 14;
	m_cubeVO.CreateNormalBufferLayout(cubeVCount, m_cube.GetIndicesSize(), 
			cubeData, m_cube.GetIndicesDataPtr());


	// load shaders
	m_shaderProgram = Shader::LoadShaders("shaders/vert.glsl", "shaders/frag.glsl");
	if (!m_shaderProgram) {
    		std::cerr << "ERROR (SHADERS) - failed to load shaders\n";
	} else {
    		std::cout << "Shader program ID: " << m_shaderProgram << std::endl;
	}
}

void Render::RenderScene(const glm::mat4& view, const glm::mat4& projection) {
	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glUseProgram(m_shaderProgram);

	// render sphere
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-1.5f, 0.0f, -2.0f));
	glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "projection"), 1, GL_FALSE, 
			&projection[0][0]);
	
	m_sphereVO.Bind();
	glDrawElements(GL_TRIANGLES, m_sphere.GetIndicesSize(), GL_UNSIGNED_INT, 0);
	

	// render cube
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(1.5f, 0.0f, -2.0f));
	glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);

	m_cubeVO.Bind();
	glDrawElements(GL_TRIANGLES, m_cube.GetIndicesSize(), GL_UNSIGNED_INT, 0);

	glEnable(GL_DEPTH_TEST);
}

GLuint Render::GetShaderProgram() const { 
	return m_shaderProgram; 
}


