// author: prisha sujin kumar
// class to handle geometry

// -- include statements -- 
// third party libraries
#include "glm/vec3.hpp"
#include "glm.vec2.hpp"
#include "glm/glm.hpp"

// std libraries
#include <assert.h>
#include <iostream>

// our libraries
#include "Geometry.hpp"
// -- end of include statements -- 

// constructor
Geometry::Geometry() {}

// destructor
Geometry::~Geometry() {}

// get buffer data size
unsigned int Geometry::GetBufferDataSize() {
	return m_bufferData.size();
}

// get buffer data pointer
float* Geometry::GetBufferDataPtr() {
	return m_bufferData.data();
}

// add vertex and associated texture coordinate and adds normal
void Geometry::AddVertex(float x, float y, float z, float s, float t) {
	// add vertex
	m_vertexPositions.push_back(x);
	m_vertexPositions.push_back(y);
	m_vertexPositions.push_back(z);

	// add texture
	m_textureCoords.push_back(s);
	m_textureCoords.push_back(t);

	// push back for normals
	m_normals.push_back(0.0f);
	m_normals.push_back(0.0f);
	m_normals.push_back(1.0f);

	// push back for tangents
	m_tangents.push_back(0.0f);
	m_tangents.push_back(0.0f);
	m_tangents.push_back(1.0f);

	// push back for bitangents
	m_bitangents.push_back(0.0f);
	m_bitangents.push_back(0.0f);
	m_bitangents.push_back(1.0f);
}

// add index
void Geometry::AddIndex(unsigned int i) {
	// index checks
	if (i >= 0 && i <= m_vertexPositions.size()/3) {
		m_indices.push_back(i);
	} else {
		std::cout << "ERROR (GEOMETRY) - invalid index\n";
	}
}

// pushes into a single vector
void Geometry::Gen() {
	assert((m_vertexPositions.size()/3) == (m_textureCoords.size()/2));

	int coordsPos = 0;
	for (int i = 0; i < m_vertexPositions.size()/3; ++i) {
		// first vertex
		// vertices
		m_bufferData.push_back(m_vertexPositions[i * 3 + 0]);
		m_bufferData.push_back(m_vertexPositions[i * 3 + 1]);
		m_bufferData.push_back(m_vertexPositions[i * 3 + 2]);

		// normals
		m_bufferData.push_back(m_normals[i * 3 + 0]);
		m_bufferData.push_back(m_normals[i * 3 + 1]);
		m_bufferData.push_back(m_normals[i * 3 + 2]);

		// textures
		m_bufferData.push_back(m_textureCoords[coordsPos * 2 + 0]);
		m_bufferData.push_back(m_textureCoords[coordsPos * 2 + 1]);
		++coordsPos; // separate counter bc it is only 2D
		
		// tangents
		m_bufferData.push_back(m_tangents[i * 3 + 0]);
		m_bufferData.push_back(m_tangents[i * 3 + 1]);
		m_bufferData.push_back(m_tangents[i * 3 + 2]);

		// bitangents
		m_bufferData.push_back(m_bitangents[i * 3 + 0]);
		m_bufferData.push_back(m_bitangents[i * 3 + 1]);
		m_bufferData.push_back(m_bitangents[i * 3 + 2]);
	}
}

// creates triangle
void MakeTriangle(unsigned int vert0, unsigned int vert1, unsigned int vert2) {
	m_indices.push_back(vert0);
	m_indices.push_back(vert1);
	m_indices.push_back(vert2);

	// look up vertex positions
	glm::vec3 pos0(m_vertexPositions[vert0 * 3 + 0], m_vertexPositions[vert0 * 3 + 1],
			m_vertexPositions[vert0 * 3 + 2]);
	glm::vec3 pos1(m_vertexPositions[vert1 * 3 + 0], m_vertexPositions[vert1 * 3 + 1],
			m_vertexPositions[vert1 * 3 + 2]);
	glm::vec3 pos2(m_vertexPositions[vert2 * 3 + 0], m_vertexPositions[vert2 * 3 + 1],
			m_vertexPositions[vert2 * 3 + 2]);

	// look up textures
	glm::vec2 tex0(m_textureCoords[vert0 * 2 + 0], m_textureCoords[vert0 * 2 + 1]);
	glm::vec2 tex1(m_textureCoords[vert1 * 2 + 0], m_textureCoords[vert1 * 2 + 1]);
	glm::vec2 tex2(m_textureCoords[vert2 * 2 + 0], m_textureCoords[vert2 * 2 + 1]);

	// create edge with two edges
	glm::vec3 edge0 = pos1 - pos0;
	glm::vec3 edge1 = pos2 - pos0;
	glm::vec2 deltaUV0 = tex1 - tex0;
	glm::vec2 deltaUV1 = tex2 - tex0;

	float f = 1.0f / (deltaUV0.x * deltaUV1.y - deltaUV1.x * deltaUV0.y);

	glm::vec3 tangent;
	glm::vec3 bitangent;

	tangent.x = f * (deltaUV1.y * edge0.x - deltaUV0.y * edge1.x);
	tangent.y = f * (deltaUV1.y * edge0.y - deltaUV0.y * edge1.y);
	tangent.z = f * (deltaUV1.y * edge0.z - deltaUV0.y * edge1.z);
	tangent = glm::normalize(tangent);

	bitangent.x = f * (-deltaUV1.x * edge0.x + deltaUV0.x * edge1.x);
	bitangent.y = f * (-deltaUV1.x * edge0.y + deltaUV0.x * edge1.y);
	bitangent.z = f * (-deltaUV1.x * edge0.z + deltaUV0.x * edge1.z);
	bitangent = glm::normalize(bitangent);

	// compute normals
	glm::vec3 normal1{m_normals[vert0 * 3 + 0], m_normals[vert0 * 3 + 1], m_normals[vert0 * 3 + 2]};
	glm::vec3 normal2{m_normals[vert1 * 3 + 0], m_normals[vert1 * 3 + 1], m_normals[vert1 * 3 + 2]};
	glm::vec3 normal3{m_normals[vert2 * 3 + 0], m_normals[vert2 * 3 + 1], m_normals[vert2 * 3 + 2]};

	m_normals[vert0 * 3 + 0] = 0.0f;	m_normals[vert0 * 3 + 1] = 0.0f;	m_normals[vert0 * 3 + 2] = 1.0f;
	m_normals[vert1 * 3 + 0] = 0.0f;	m_normals[vert1 * 3 + 1] = 0.0f;	m_normals[vert1 * 3 + 2] = 1.0f;
	m_normals[vert2 * 3 + 0] = 0.0f;	m_normals[vert2 * 3 + 1] = 0.0f;	m_normals[vert2 * 3 + 2] = 1.0f;

	// compute tangents
	m_tangents[vert0 * 3 + 0] = tangent.x;	m_tangents[vert0 * 3 + 1] = tangent.y;	m_tangents[vert0 * 3 + 2] = tangent.z;
	m_tangents[vert1 * 3 + 0] = tangent.x;	m_tangents[vert1 * 3 + 1] = tangent.y;	m_tangents[vert1 * 3 + 2] = tangent.z;
	m_tangents[vert2 * 3 + 0] = tangent.x;	m_tangents[vert2 * 3 + 1] = tangent.y;	m_tangents[vert2 * 3 + 2] = tangent.z;

	// compute bitangents
	m_bitangents[vert0 * 3 + 0] = bitangent.x;	m_bitangents[vert0 * 3 + 1] = bitangent.y;	m_bitangents[vert0 * 3 + 2] = bitangent.z;
	m_bitangents[vert1 * 3 + 0] = bitangent.x;	m_bitangents[vert1 * 3 + 1] = bitangent.y;	m_bitangents[vert1 * 3 + 2] = bitangent.z;
	m_bitangents[vert2 * 3 + 0] = bitangent.x;	m_bitangents[vert2 * 3 + 1] = bitangent.y;	m_bitangents[vert2 * 3 + 2] = bitangent.z;
}

// get indices size
unsigned int Geometry::GetIndicesSize() {
	return m_indices.size();
}

// get indices data pointer
unsigned int* Geometry::GetIndicesDataPtr() {
	return m_indices.data();
}

