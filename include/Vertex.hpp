#ifndef VERTEX_HPP
#define VERTEX_HPP
// author: prisha sujin kumar
// desc: class to set up vertex buffer layouts

class Vertex {
	public:
		/**
 		* @brief constructs a Vertex object
 		**/ 
		Vertex();

		/**
 		* @brief deallocates memory and cleans up
 		**/ 
		~Vertex();

		/**
 		* @brief binds buffer
 		**/ 
		void Bind();

		/**
 		* @brief unbinds buffer
 		**/ 
		void Unbind();

		/**
 		* @brief creates position buffer layout
		* @param unsigned int vcount, unsigned int icount, float* vadata, unsigned int* idata
 		**/ 
		void CreatePositionBufferLayout(unsigned int vcount, unsigned int icount, float* vdata, unsigned int* idata);
		
		/**
 		* @brief creates texture buffer layout
		* @param unsigned int vcount, unsigned int icount, float* vdata, unsigned int* idata
 		**/ 
		void CreateTextureBufferLayout(unsigned int vcount, unsigned int icount, float* vdata, unsigned int* idata);
		
		/**
 		* @brief creates normal buffer layout
		* @param unsigned int vcount, unsigned int icount, float* vdata, unsigned int* idata
 		**/ 
		void CreateNormalBufferLayout(unsigned int vcount, unsigned int icount, float* vdata, unsigned int* idata);
	private:
		// vertex array object
		GLuint m_VAOId;
		// vertex buffer 
		GLuint m_vertexPositionBuffer;
		// index buffer object
		GLuint m_indexBufferObject;
		// stride
		unsigned int m_stride{0};
};

#endif
