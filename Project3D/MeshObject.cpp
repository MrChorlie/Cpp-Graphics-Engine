#include "MeshObject.h"
#include "Application3D.h"

MeshObject::MeshObject()
{
	// Load shader
	m_shader.loadShader(aie::eShaderStage::VERTEX, "./shaders/noTexture.vert");
	m_shader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/noTexture.frag");

	if (m_shader.link() == false)
	{
		printf("Shader Error: %s\n", m_shader.getLastError());
		return;
	}
	
	// Load mesh
	if (m_mesh.load("./models/bunny.obj") == false)
	{
		printf("Bunny Mesh Error!\n");
		return;
	}

	// Set transform to a default value
	m_transform = {
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1 };
}

MeshObject::MeshObject(std::string name, std::string meshFileName, bool textured)
{
	m_name = name;
	// Load shader

	if (textured)
	{
		m_shader.loadShader(aie::eShaderStage::VERTEX, "./shaders/textured.vert");
		m_shader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/textured.frag");
	}
	else
	{
		m_shader.loadShader(aie::eShaderStage::VERTEX, "./shaders/noTexture.vert");
		m_shader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/noTexture.frag");
	}

	if (m_shader.link() == false)
	{
		printf("Shader Error: %s\n", m_shader.getLastError());
		return;
	}

	// Set up file path
	std::string startPath = "./models/";
	std::string fullPath = startPath + meshFileName;

	// Load mesh
	if (m_mesh.load(fullPath.c_str(), true, true) == false)
	{
		printf("Mesh Error!\n");
		return;
	}

	// Set transform to a default value
	m_transform = {
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1 };
}

glm::vec3 MeshObject::getPos()
{
	glm::vec3 position;

	position.x = m_transform[3].x;
	position.y = m_transform[3].y;
	position.z = m_transform[3].z;

	return position;
}

void MeshObject::setPos(glm::vec3 position)
{
	m_transform[3].x = position.x;
	m_transform[3].y = position.y;
	m_transform[3].z = position.z;
}

glm::vec3 MeshObject::getScale()
{
	glm::vec3 scale;

	scale.x = m_transform[0].x;
	scale.y = m_transform[1].y;
	scale.z = m_transform[2].z;

	return scale;
}

void MeshObject::setScale(glm::vec3 scale)
{
	m_transform[0].x = scale.x;
	m_transform[1].y = scale.y;
	m_transform[2].z = scale.z;
}

/// <summary>
/// draw is used to render the object
/// </summary>
void MeshObject::draw()
{
	m_mesh.draw();
}

/// <summary>
/// bindShader is used to bind all the neccesary uniforms
/// </summary>
void MeshObject::bindShader(glm::vec3 ambientLight, glm::vec3 lightColour, glm::vec3 lightDirection, \
	glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraPosition, 
	int numLights, glm::vec3 pointLightColours[], glm::vec3 pointLightPositions[])
{

	// Bind shader
	m_shader.bind();

	// Bind light
	m_shader.bindUniform("AmbientColour", ambientLight);
	m_shader.bindUniform("LightColour", lightColour);
	m_shader.bindUniform("LightDirection", lightDirection);

	m_shader.bindUniform("cameraPosition", cameraPosition);

	m_shader.bindUniform("numLights", numLights);
	m_shader.bindUniform("PointLightPosition", numLights, pointLightPositions);
	m_shader.bindUniform("PointLightColour", numLights, pointLightColours);

	// Bind transform
	auto pvm = projectionMatrix * viewMatrix * m_transform;
	m_shader.bindUniform("ProjectionViewModel", pvm);

	// Bind transforms for lighting 
	m_shader.bindUniform("ModelMatrix", m_transform);
}