#include "Mesh.h"
#include <gl_core_4_4.h>

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

/// <summary>
/// initialise is used to initialise any mesh
/// </summary>
void Mesh::initialise(unsigned int vertexCount, const Vertex* vertices, unsigned int indexCount, unsigned int* indices)
{
	// Check that the mesh is not initiliased already
	assert(vao == 0);

	// Generate buffers
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	// Bind vertex array, a mesh wrapper
	glBindVertexArray(vao);

	// Bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	// Enable first element as position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	// Enable second element as position
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)16);

	// Bind indices if there are any
	if (indexCount != 0)
	{
		glGenBuffers(1, &ibo);

		// Bind vertex buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		// Fill vertex buffer
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

		triCount = indexCount / 3;
	}
	else
	{
		triCount = indexCount / 3;
	}

	// Unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/// <summary>
/// initialiseQuad is used to make a quad and put it into the correct buffers
/// </summary>
void Mesh::initialiseQuad()
{
	// define 4 vertices for 2 triangles 
	Mesh::Vertex vertices[4];
	vertices[0].position = { -0.5f, 0, 0.5f, 1 };
	vertices[1].position = { 0.5f, 0, 0.5f, 1 };
	vertices[2].position = { -0.5f, 0, -0.5f, 1 };
	vertices[3].position = { 0.5f, 0, -0.5f, 1 };

	vertices[0].normal = { 0, 1, 0, 0 };
	vertices[1].normal = { 0, 1, 0, 0 };
	vertices[2].normal = { 0, 1, 0, 0 };
	vertices[3].normal = { 0, 1, 0, 0 };

	unsigned int indices[6] = { 0, 1, 2, 
								2, 1, 3 };

	initialise(4, vertices, 6, indices);
}

/// <summary>
/// initialiseCube is used to make a quad
/// </summary>
void Mesh::initialiseCube() 
{
	Mesh::Vertex vertices[8];
	vertices[0].position = { -1, -1, 1, 1 };
	vertices[1].position = { 1, -1, 1, 1 };
	vertices[2].position = { 1, 1, 1, 1 };
	vertices[3].position = { -1, 1, 1, 1 };
	vertices[4].position = { -1, -1, -1, 1 };
	vertices[5].position = { 1, -1, -1, 1 };
	vertices[6].position = { 1, 1, -1, 1 };
	vertices[7].position = { -1, 1, -1, 1 };

	unsigned int indices[36] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	initialise(8, vertices, 36, indices);
}

/// <summary>
/// draw is used to show the object on the screen
/// </summary>
void Mesh::draw()
{
	glBindVertexArray(vao);

	// Using indices or just vertices
	if (ibo != 0)
	{
		glDrawElements(GL_TRIANGLES, 3 * triCount, GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, 3 * triCount);
	}
}