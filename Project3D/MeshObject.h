#pragma once

#include "Mesh.h"
#include "OBJMesh.h"
#include "Shader.h"
#include <string>
#include <glm/mat4x4.hpp>

class MeshObject
{
private:
	
	std::string m_name;

	aie::OBJMesh m_mesh;
	glm::mat4 m_transform;
	aie::ShaderProgram m_shader;

public:
	/// Constructors
	MeshObject();
	MeshObject(std::string name, std::string meshFileName, bool textured);

	// Getters and Setters
	std::string getName() { return m_name; }
	void setName(std::string name) { m_name = name; }

	glm::vec3 getPos();
	void setPos(glm::vec3 position);

	glm::vec3 getScale();
	void setScale(glm::vec3 scale);

	/// <summary>
	/// draw is used to render the object
	/// </summary>
	virtual void draw();

	/// <summary>
	/// bindShader is used to bind all the neccesary uniforms
	/// </summary>
	void bindShader(glm::vec3 ambientLight, glm::vec3 lightColour, glm::vec3 lightDirection,
		glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraPosition,
		int numLights, glm::vec3 pointLightColours[], glm::vec3 pointLightPositions[]);
};