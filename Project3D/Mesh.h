#pragma once

#include <glm/glm.hpp>

/// <summary>
/// The Mesh class is used to store the informations about its verices, indices and triangles
/// </summary>
class Mesh
{
public:

	/// <summary>
	/// Default Constuctor
	/// </summary>
	Mesh() : triCount(0), vao(0), vbo(0), ibo(0) {}
	virtual ~Mesh();

	/// <summary>
	/// Vertex is a struct used to store data about its position, normal, etc.
	/// </summary>
	struct Vertex
	{
		glm::vec4 position;
		glm::vec4 normal;
		glm::vec2 texCoord;
	};

	/// <summary>
	/// initialise is used to initialise any mesh
	/// </summary>
	void initialise(unsigned int vertexCount, const Vertex* vertices,
					unsigned int indexCount = 0,
					unsigned int* indices = nullptr);

	/// <summary>
	/// initialiseQuad is used to make a quad
	/// </summary>
	void initialiseQuad();

	/// <summary>
	/// initialiseCube is used to make a quad
	/// </summary>
	void initialiseCube();

	/// <summary>
	/// draw is used to show the object on the screen
	/// </summary>
	virtual void draw();

protected:

	unsigned int triCount;
	unsigned int vao, vbo, ibo;

};