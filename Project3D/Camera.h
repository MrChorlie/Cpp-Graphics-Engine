#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Input.h>

class Camera
{
private:

	float m_theta;
	float m_phi;
	glm::vec3 m_position;
	float m_speed;
		
	float m_lastMouseX;
	float m_lastMouseY;

public:
	// Constructors
	Camera();

	// getters and setters
	glm::vec3 getPosition() { return m_position; }
	void setPosition(glm::vec3 position) { m_position = position; }

	/// <summary>
	/// getViewMatrix returns the current view matrix of the camera
	/// <summary>
	glm::mat4 getViewMatrix();

	/// <summary>
	/// getProjectionMatrix returns the current projection matrix of the camera
	/// <summary>
	glm::mat4 getProjectionMatrix(float w, float h);

	/// <summary>
	/// update is called once every frame
	/// </summary>
	void update(float deltaTime);
};