#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP
// author: prisha sujin kumar
// class to store vertice information

// std libraries
#include <vector>

class Geometry {
	public:
		/**
 		* @brief constructs a Geometry object
 		**/ 
		Geometry();
		
		/**
 		* @brief deallocates memory and cleans up
 		**/
		~Geometry();
		
		/**
 		* @brief returns buffer data size
 		* @return unsigned int
		**/
		unsigned int GetBufferDataSize();

		/**
 		* @brief returns buffer data pointer
 		* @return float*
 		**/ 
		float* GetBufferDataPtr();
	
		/**
 		* @brief adds vertex, associated texture, and associated normal
 		* @param float x, float y, float z, float s, float t
 		**/ 
		void AddVertex(float x, float y, float z, float s, float t);
		
		/**
 		* @brief adds index
 		* @param unsigned int i
 		**/ 
		void AddIndex(unsigned int i);

		/**
 		* @brief generates Geometry object and pushes into a single vector
 		**/ 
		void Gen();

		/**
 		* @brief returns indices size
 		* @return unsigned int
 		**/ 
		unsigned int GetIndicesSize();

		/**
 		* @brief returns indices data pointer
 		* @return unsigned int*
 		**/ 
		unsigned int* GetIndicesDataPtr();

		/**
 		* @brief generates a sphere
		* @param float radius, int sectorCount, int stackCount (default of 1.0f, 36, 18)
 		**/ 
		void GenerateSphere(float radius = 1.0f, 
                       int sectorCount = 36, 
                       int stackCount = 18);

		/**
 		* @brief generates a cube
		* @param float size (default of 1.0f)
 		**/ 
		void GenerateCube(float size = 1.0f);

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

#endif // GEOMETRY_HPP

