// author: prisha sujin kumar
// desc: class to handle geometry

// third party libraries
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "glm/glm.hpp"

// std libraries
#include <assert.h>
#include <iostream>

// our libraries
#include "Geometry.hpp"

Geometry::Geometry() {}

Geometry::~Geometry() {}

unsigned int Geometry::GetBufferDataSize() {
	return m_bufferData.size();
}

float* Geometry::GetBufferDataPtr() {
	return m_bufferData.data();
}

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

void Geometry::AddIndex(unsigned int i) {
	// index checks
	if (i >= 0 && i <= m_vertexPositions.size()/3) {
		m_indices.push_back(i);
	} else {
		std::cout << "ERROR (GEOMETRY) - invalid index\n";
	}
}

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

	//std::cout << "first vertex: ";
	//for(int i = 0; i < 14; i++) {
	//	std::cout << m_bufferData[i] << " ";
	//}
	//std::cout << std::endl;
}

unsigned int Geometry::GetIndicesSize() {
	return m_indices.size();
}

unsigned int* Geometry::GetIndicesDataPtr() {
	return m_indices.data();
}

void Geometry::GenerateFloor(float size) {
	m_vertexPositions.clear();
	m_indices.clear();

	float half = size / 2.0f;

	AddVertex(-half, 0.0f, -half, 0.0f, 0.0f);
	AddVertex(half, 0.0f, -half, 1.0f, 0.0f);
	AddVertex(half, 0.0f, half, 1.0f, 1.0f);
	AddVertex(-half, 0.0f, half, 0.0f, 1.0f);

	m_indices = {
		0, 1, 2,
		0, 2, 3
	};

	for (int i = 0; i < 4; i++) {
		m_normals[i * 3 + 0] = 0.0f;
		m_normals[i * 3 + 1] = 1.0f;
		m_normals[i * 3 + 2] = 0.0f;
	}

	Gen();

}

void Geometry::GenerateSphere(float radius, int sectorCount, int stackCount) {
	m_vertexPositions.clear();
    	m_indices.clear();
    	m_bufferData.clear();

    	const float PI = acos(-1.0f);
    
    	// position vertices
	for(int i = 0; i <= stackCount; ++i) {
        	float stackAngle = PI/2 - PI * i / stackCount;
        	float xy = radius * cosf(stackAngle);
        	float z = radius * sinf(stackAngle);
		
		for(int j = 0; j <= sectorCount; ++j) {
            		float sectorAngle = 2 * PI * j / sectorCount;
            		AddVertex(xy * cosf(sectorAngle), xy * sinf(sectorAngle), z, 0, 0);
        	}
    	}

	// normals
	m_normals.clear();
	for (size_t i = 0; i < m_vertexPositions.size(); i += 3) {
		glm::vec3 pos(
				m_vertexPositions[i],
				m_vertexPositions[i + 1],
				m_vertexPositions[i + 2]
			     );

		glm::vec3 normal = glm::normalize(pos);

		m_normals.push_back(normal.x);
		m_normals.push_back(normal.y);
		m_normals.push_back(normal.z);
	}

    	// indices
    	m_indices.clear();
	for(int i = 0; i < stackCount; ++i) {
        	int k1 = i * (sectorCount + 1);
        	int k2 = k1 + sectorCount + 1;

        	for(int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
            		if(i != 0) { // first triangle 
                		m_indices.insert(m_indices.end(), {
						static_cast<unsigned int>(k1), static_cast<unsigned int>(k2), 
						static_cast<unsigned int>(k1 + 1)});
			} if(i != (stackCount-1)) {
				m_indices.insert(m_indices.end(), {
						static_cast<unsigned int>(k1 + 1), static_cast<unsigned int>(k2), 
						static_cast<unsigned int>(k2 + 1)});
			}
		}
	}
	Gen();
}

void Geometry::GenerateCube(float size) {   
	m_vertexPositions.clear();
    	m_indices.clear();
    	m_bufferData.clear();

	float half = size / 2.0f;

	// front
	AddVertex(-half, -half, half, 0.0f, 0.0f);
	AddVertex(half, -half, half, 1.0f, 0.0f);
	AddVertex(half, half, half, 1.0f, 1.0f);
	AddVertex(-half, half, half, 0.0f, 1.0f);

	// back
	AddVertex(-half, -half, -half, 0.0f, 0.0f);
	AddVertex(half, -half, -half, 1.0f, 0.0f);
	AddVertex(half, half, -half, 1.0f, 1.0f);
	AddVertex(-half, half, -half, 0.0f, 1.0f);

	// left
	AddVertex(-half, -half, -half, 0.0f, 0.0f);
	AddVertex(-half, -half, half, 1.0f, 0.0f);
	AddVertex(-half, half, half, 1.0f, 1.0f);
	AddVertex(-half, half, -half, 0.0f, 1.0f);

	// right
	AddVertex(half, -half, half, 0.0f, 0.0f);
	AddVertex(half, -half, -half, 1.0f, 0.0f);
	AddVertex(half, half, -half, 1.0f, 1.0f);
	AddVertex(half, half, half, 0.0f, 1.0f);

	// top
	AddVertex(-half, half, half, 0.0f, 0.0f);
	AddVertex(half, half, half, 1.0f, 0.0f);
	AddVertex(half, half, -half, 1.0f, 1.0f);
	AddVertex(-half, half, -half, 0.0f, 1.0f);

	// bottom
	AddVertex(-half, -half, -half, 0.0f, 0.0f);
	AddVertex(half, -half, -half, 1.0f, 0.0f);
	AddVertex(half, -half, half, 1.0f, 1.0f);
	AddVertex(-half, -half, half, 0.0f, 1.0f);

	// normals
	
	unsigned int indices[] = {
		0, 1, 2, 2, 3, 0,
		4, 5, 6, 6, 7, 4,
		8, 9, 10, 10, 11, 8,
		12, 13, 14, 14, 15, 12,
		16, 17, 18, 18, 19, 16,
		20, 21, 22, 22, 23, 20
	};

	m_indices.insert(m_indices.end(), std::begin(indices), std::end(indices));
	
	m_normals.clear();

	for (int i = 0; i < 4; i++) {
		m_normals.insert(m_normals.end(), {0, 0, 1});
	} for (int i = 0; i < 4; i++) {
		m_normals.insert(m_normals.end(), {0, 0, -1});
	} for (int i = 0; i < 4; i++) {
		m_normals.insert(m_normals.end(), {-1, 0, 0});
	} for (int i = 0; i < 4; i++) {
		m_normals.insert(m_normals.end(), {1, 0, 0});
	} for (int i = 0; i < 4; i++) {
		m_normals.insert(m_normals.end(), {0, 1, 0});
	} for (int i = 0; i < 4; i++) {
		m_normals.insert(m_normals.end(), {0, -1, 0});
	}

	Gen();
}

