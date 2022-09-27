#include "Camera.h"

Camera::Camera()
{
	m_phi = 0;
	m_theta = 0;
	m_position = { -10, 2, 0 };
	m_speed = 10;
}

/// <summary>
/// getViewMatrix returns the current view matrix of the camera
/// <summary>
glm::mat4 Camera::getViewMatrix() 
{
	// Find the radians of theta and phi
	float thetaR = glm::radians(m_theta);
	float phiR = glm::radians(m_phi);

	glm::vec3 forward(cos(phiR) * cos(thetaR), sin(phiR), cos(phiR) * sin(thetaR));

	return glm::lookAt(m_position, m_position + forward, glm::vec3(0, 1, 0));
}

/// <summary>
/// getProjectionMatrix returns the current projection matrix of the camera
/// <summary>
glm::mat4 Camera::getProjectionMatrix(float w, float h)
{
	return glm::perspective(glm::pi<float>() * 0.25f, w / h, 0.1f, 1000.f);
}

/// <summary>
/// update is called once every frame
/// </summary>
void Camera::update(float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();
	float thetaR = glm::radians(m_theta);
	float phiR = glm::radians(m_phi);

	//calculate the forwards and right axes and up axis for the camera 
	glm::vec3 forward(cos(phiR) * cos(thetaR), sin(phiR), cos(phiR) * sin(thetaR));
	glm::vec3 right(-sin(thetaR), 0, cos(thetaR));
	glm::vec3 up(0, 1, 0);

	// use WASD, ZX keys to move camera around 
	if (input->isKeyDown(aie::INPUT_KEY_X))
		m_position += up * (deltaTime * m_speed);
	if (input->isKeyDown(aie::INPUT_KEY_Z))
		m_position += -up * (deltaTime * m_speed);

	if (input->isKeyDown(aie::INPUT_KEY_W))
		m_position += forward * (deltaTime * m_speed);
	if (input->isKeyDown(aie::INPUT_KEY_S))
		m_position += -forward * (deltaTime * m_speed);
	if (input->isKeyDown(aie::INPUT_KEY_D))
		m_position += right * (deltaTime * m_speed);
	if (input->isKeyDown(aie::INPUT_KEY_A))
		m_position += -right * (deltaTime * m_speed);

	// get the current mouse coordinates 
	float mx = input->getMouseX();
	float my = input->getMouseY();
	const float turnSpeed = 0.05f;
	// if the right button is down, increment theta and phi 
	if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_RIGHT))
	{
		m_theta += turnSpeed * (mx - m_lastMouseX);
		m_phi += turnSpeed * (my - m_lastMouseY);
	}
	// store this frames values for next frame 
	m_lastMouseX = mx;
	m_lastMouseY = my;
}