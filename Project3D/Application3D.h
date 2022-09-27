#pragma once

#include "Application.h"
#include "Mesh.h"
#include "OBJMesh.h"
#include "Shader.h"
#include "MeshObject.h"
#include "Camera.h"
#include <vector>
#include <glm/mat4x4.hpp>

const int MAX_LIGHTS = 4;

class Application3D : public aie::Application {
public:

	/// <summary>
	/// Default Constructor
	/// </summary>
	Application3D();
	virtual ~Application3D();

	/// <summary>
	/// startup is used to start the functions of the application
	/// </summary>
	virtual bool startup();
	/// <summary>
	/// shutdown is used to stop the fuctions of the application
	/// </summary>
	virtual void shutdown();

	/// <summary>
	/// update is called once every frame
	/// </summary>
	virtual void update(float deltaTime);
	/// <summary>
	/// draw is used to draw all the graphics
	/// </summary>
	virtual void draw();

	/// <summary>
	/// addObject is used to add an object to the list of objects in the scene
	/// </summary>
	void addObject(MeshObject* object);
	/// <summary>
	/// removeObject is used to remove an object from the list of objects in the scene
	/// </summary>
	void removeObject(MeshObject* object);

	/// <summary>
	/// uiLogic is used to setup the UI for the engine
	/// </summary>
	void uiLogic();


protected:

	// Lights

	struct Light {
		Light() {}

		Light(glm::vec3 pos, glm::vec3 col)
		{
			direction = pos;
			colour = col;
		}

		glm::vec3 direction;
		glm::vec3 colour;
	};

	Light m_sunLight;
	std::vector<Light> m_pointLights;
	glm::vec3 m_ambientLight;
	glm::vec3 m_pointLightPositions[MAX_LIGHTS];
	glm::vec3 m_pointLightColours[MAX_LIGHTS];
	Light* m_selectedPointLight;

	std::vector<MeshObject*> m_objects;
	MeshObject* m_selectedObject;

	Mesh m_quad;

	// Inspector variables
	glm::vec3 inspPosition;
	glm::vec3 inspScale;

	Camera m_camera;
};