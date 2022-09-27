#include "Application3D.h"
#include "Gizmos.h"
#include "Input.h"
#include "imgui.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "gl_core_4_4.h"
#include <string>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

/// <summary>
/// Default Constructor
/// </summary>
Application3D::Application3D() {

}

Application3D::~Application3D() {

}

/// <summary>
/// startup is used to start the functions of the application
/// </summary>
bool Application3D::startup() {
	
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	m_sunLight.direction = { 1, 0, 0 };
	m_sunLight.colour = { 1, 1, 0 };
	m_ambientLight = { 0.25f, 0.25f , 0.25f };

	MeshObject* object1 = new MeshObject("Spear", "soulspear.obj", true);

	addObject(object1);

	MeshObject* object2 = new MeshObject("Dragon", "dragon.obj", false);

	object2->setPos({ 0, 0, -5 });
	object2->setScale({ 0.25, 0.25, 0.25});

	addObject(object2);

	MeshObject* object3 = new MeshObject("Bunny", "bunny.obj", false);

	object3->setPos({ 0, 0, 5 });
	object3->setScale({ 0.25, 0.25, 0.25 });

	addObject(object3);

	// red light on the left 
	m_pointLights.push_back(Light(vec3(0, 3, 5), vec3(50, 0, 0)));
	// green light on the right 
	m_pointLights.push_back(Light(vec3(0, 3, -5), vec3(0, 50, 0)));

	m_quad.initialiseQuad();

	m_selectedObject = nullptr;
	m_selectedPointLight = nullptr;

	return true;
}

/// <summary>
/// shutdown is used to stop the fuctions of the application
/// </summary>
void Application3D::shutdown() {

	Gizmos::destroy();
}

/// <summary>
/// update is called once every frame
/// </summary>
void Application3D::update(float deltaTime) {

	// query time since application started
	float time = getTime();

	uiLogic();

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	m_camera.update(deltaTime);
}

/// <summary>
/// draw is used to draw all the graphics
/// </summary>
void Application3D::draw() {

	glDisable(GL_BLEND);

	// wipe the screen to the background colour
	clearScreen();

	// get the projections and view matricies from the camera
	glm::mat4 projectionMatrix = m_camera.getProjectionMatrix(getWindowWidth(), getWindowHeight());

	glm::mat4 viewMatrix = m_camera.getViewMatrix();

	// fill the point light arrays
	for (int i = 0; i < MAX_LIGHTS && i < m_pointLights.size(); i++)
	{
		m_pointLightPositions[i] = m_pointLights[i].direction;
		m_pointLightColours[i] = m_pointLights[i].colour;
	}

	for (auto pObject : m_objects)
	{
		pObject->bindShader(m_ambientLight, m_sunLight.colour, m_sunLight.direction, 
			viewMatrix, projectionMatrix, m_camera.getPosition(), 
			MAX_LIGHTS, m_pointLightColours, m_pointLightPositions);
		pObject->draw();
	}
}

/// <summary>
/// addObject is used to add an object to the list of objects in the scene
/// </summary>
void Application3D::addObject(MeshObject* object)
{
	m_objects.push_back(object);
}

/// <summary>
/// uiLogic is used to setup the UI for the engine
/// </summary>
void Application3D::uiLogic()
{
	// Light
	ImGui::Begin("Light Settings");
	ImGui::SetWindowSize(ImVec2(400, 100));
	ImGui::SetWindowPos(ImVec2(getWindowWidth() - 400, 0));
	ImGui::DragFloat3("Sunlight Direction", &m_sunLight.direction[0], 0.1f, -1.0f, 1.0f);
	ImGui::DragFloat3("Sunlight Colour", &m_sunLight.colour[0], 0.1f, 0.0f, 2.0f);
	ImGui::DragFloat3("Ambient Light", &m_ambientLight[0], 0.1f, 0.0f, 2.0f);
	ImGui::End();

	// Point Lights
	// Hiearchy
	ImGui::Begin("Point Light Hiearchy");
	ImGui::SetWindowSize(ImVec2(100, 200));
	ImGui::SetWindowPos(ImVec2(getWindowWidth() - 100, 100));
	for (int i = 0; i < m_pointLights.size(); i++)
	{
		if (ImGui::Button(std::to_string(i).c_str()))
		{
			m_selectedPointLight = &m_pointLights[i];
		}
	}
	ImGui::End();

	if (m_selectedPointLight != nullptr)
	{
		ImGui::Begin("Point Light Inspector");
		ImGui::SetWindowSize(ImVec2(300, 200));
		ImGui::SetWindowPos(ImVec2(getWindowWidth() - 400, 100));
		ImGui::DragFloat3("Position", &m_selectedPointLight->direction[0], 0.1f, -100.0f, 100.0f);
		ImGui::DragFloat3("Colour", &m_selectedPointLight->colour[0], 1.0f, 0.0f, 255.0f);
		ImGui::End();
	}

	// Hiearchy
	ImGui::Begin("Hiearchy");
	ImGui::SetWindowSize(ImVec2(100, 200));
	ImGui::SetWindowPos(ImVec2(0, 0));
	for (auto pObject : m_objects)
	{
		if (ImGui::Button(pObject->getName().c_str()))
		{
			m_selectedObject = pObject;
		}
	}
	ImGui::End();

	// Inspector Settings
	if (m_selectedObject != nullptr)
	{
		ImGui::Begin("Inspector");
		ImGui::SetWindowSize(ImVec2(300, 200));
		ImGui::SetWindowPos(ImVec2(100, 0));
		ImGui::Text(m_selectedObject->getName().c_str());
		if (ImGui::DragFloat3("Position", &inspPosition[0], 0.1f, -100.0f, 100.0f))
		{
			m_selectedObject->setPos(inspPosition);
		}
		inspPosition = m_selectedObject->getPos();

		if (ImGui::DragFloat3("Scale", &inspScale[0], 0.1f, -100.0f, 100.0f))
		{
			m_selectedObject->setScale(inspScale);
		}
		inspScale = m_selectedObject->getScale();
		ImGui::End();
	}
}