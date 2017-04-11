#pragma once
#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>

class MyCamera
{
public:
	float mousedX;
	float mousedY;

	float mouseSensitivityVert;
	float mouseSensitivityHoriz;

	float mouseXLastFrame;
	float mouseYLastFrame;

	MyCamera();
	
	glm::mat4 GetView(void);
	glm::mat4 GetProjection(bool);
	void SetPosition(vector3);
	vector3 GetPosition(void);
	void SetTarget(vector3);

	void SetUp(vector3);
	void MoveForward(float);
	void MoveSideways(float);
	void MoveVertical(float);

	void ChangePitch(float);
	void ChangeRoll(float);
	void ChangeYaw(float);

	~MyCamera();



private:
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	glm::quat cam_quat;

	float fPitch;
	float fRoll;
	float fYaw;

	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 up;
	glm::vec3 forward;
	glm::vec3 right;
};

