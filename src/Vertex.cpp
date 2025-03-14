// author: prisha sujin kumar
// desc: class to handle vertex buffer layout

// third party libraries
#include <glad/glad.h>

// std libraries
#include <iostream>

// our libraries
#include "Vertex.hpp"

Vertex::Vertex() {}

Vertex::~Vertex() {
	glDeleteBuffers(1, &m_vertexPositionBuffer);
	glDeleteBuffers(1, &m_indexBufferObject);
}

void Vertex::Bind() {
	glBindVertexArray(m_VAOId);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexPositionBuffer);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Vertex::Unbind() {
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Vertex::CreatePositionBufferLayout(unsigned int vcount, unsigned int icount, float* vdata, unsigned int* idata) {
	m_stride = 3;
	static_assert(sizeof(GLfloat)==sizeof(float), "GLFloat and gloat are not the same size on this architecture");

	glGenVertexArrays(1, &m_VAOId);
	glBindVertexArray(m_VAOId);

	glGenBuffers(1, &m_vertexPositionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexPositionBuffer);
	glBufferData(GL_ARRAY_BUFFER, vcount*3*sizeof(float), vdata, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*m_stride, 0);
	static_assert(sizeof(unsigned int)==sizeof(GLuint), "GLuint is not the same size");

	glGenBuffers(1, &m_indexBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, icount*sizeof(unsigned int), idata, GL_STATIC_DRAW);
}

void Vertex::CreateTextureBufferLayout(unsigned int vcount, unsigned int icount, float* vdata, unsigned int* idata) {
	m_stride = 5;
	static_assert(sizeof(GLfloat)==sizeof(float), "GLFloat and gloat are not the same size on this architecture");

	glGenVertexArrays(1, &m_VAOId);
	glBindVertexArray(m_VAOId);

	glGenBuffers(1, &m_vertexPositionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexPositionBuffer);
	glBufferData(GL_ARRAY_BUFFER, vcount*5*sizeof(float), vdata, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*m_stride, 0);

	// add texture
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, sizeof(float)*m_stride, (char*)(sizeof(float)*3));
	static_assert(sizeof(unsigned int)==sizeof(GLuint), "GLuint is not the same size");

	glGenBuffers(1, &m_indexBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, icount*sizeof(unsigned int), idata, GL_STATIC_DRAW);

}

void Vertex::CreateNormalBufferLayout(unsigned int vcount, unsigned int icount, float* vdata, unsigned int* idata) {
	m_stride = 14;
	static_assert(sizeof(GLfloat)==sizeof(float), "GLFloat and gloat are not the same size on this architecture");

	glGenVertexArrays(1, &m_VAOId);
	glBindVertexArray(m_VAOId);

	glGenBuffers(1, &m_vertexPositionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexPositionBuffer);
	glBufferData(GL_ARRAY_BUFFER, vcount * 14 * sizeof(float), vdata, GL_STATIC_DRAW);
	

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14*sizeof(float), (void*)0);

	// add normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14*sizeof(float), (void*)(3*sizeof(float)));  
	// add texture
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14*sizeof(float), (void*)(6*sizeof(float))); 

	// add tangent
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14*sizeof(float), (void*)(8*sizeof(float)));

	// add bi-tangent
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14*sizeof(float), (void*)(11*sizeof(float))); 

	static_assert(sizeof(unsigned int)==sizeof(GLuint), "GLuint is not the same size");

	// index buffer
	glGenBuffers(1, &m_indexBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, icount*sizeof(unsigned int), idata, GL_STATIC_DRAW);
}






