#ifndef VERTEX_HPP
#define VERTEX_HPP

// class to set up vertex buffer layouts

// -- include statements --
// third party libraries
// std libraries
// our libraries
// -- end of include statements --

class Vertex {
	public:
		// constructor
		Vertex();
		// destructor
		~Vertex();
		// binds
		void Bind();
		// unbinds
		void Unbind();
		// create position buffer layout
		void CreatePositionBufferLayout(unsigned int vcount, unsigned int icount, float* vdata, unsigned int* idata);
		// create texture buffer layout
		void CreateTextureBufferLayout(unsigned int vcount, unsigned int icount, float* vdata, unsigned int* idata);
		// create normal buffer layout
		void CreateNormalbufferLayout(unsigned int vcount, unsigned int icount, float* vdata, unsigned int* idata);
	private:
		// vertex array object
		GLuint m_VAOId;
		// vertex buffer
		GLuint m_vertexPositionBuffer;
		// index buffer
		GLuint m_indexBufferObject;
		// stride
		unsigned int m_stride{0};
};

#endif
