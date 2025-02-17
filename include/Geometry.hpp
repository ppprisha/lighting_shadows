#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP
// class to store vertice information

// -- include statements -- 
// third party libraries
// std libraries
#include <vector>

// our libraries
// -- end of include statements -- 

class Geometry {
	public:
		// constructor
		Geometry();
		// destructor
		~Geometry();
		// get buffer data size
		unsigned int GetBufferDataSize();
		// get buffer data pointer
		float* GetBufferDataPtr();
		// add vertex
		void AddVertex(float x, float y, float z, float s, float t);
		// add index
		void AddIndex(unsigned int i);
		// pushes into a single vector
		void Gen();
		// creates triangle
		void MakeTriangle(unsigned int vert0, unsigned int vert1, unsigned int vert2);
		// get indices size
		unsigned int GetIndicesSize();
		// get indices data pointer
		unsigned int* GetIndicesDataPtr();
	private:
		// stores all positions, coordinates, normals
		std::vector<float> m_bufferData;

		// broken down into...
		std::vector<float> m_vertexPositions;
		std::vector<float> m_textureCoords;
		std::vector<float> m_normals;
		std::vector<float> m_tangents;
		std::vector<float> m_bitangents;

		// indices for triangle mesh
		std::vector<unsigned int> m_indices;
};

