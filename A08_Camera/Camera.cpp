#include "Camera.h"

MyCamera::MyCamera()
{
	position = glm::vec3(0.0f, 0.0f, -20.0f);
	
	forward = glm::vec3(0.0f, 0.0f, 1.0f);
	right = glm::vec3(1.0f, 0.0f, 0.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	
	fPitch = 0.0f;
	fYaw = 0.0f;
	fRoll = 0.0f;

	mousedX = 0;
	mousedY = 0;

	mouseSensitivityVert = 0.002f;
	mouseSensitivityHoriz = 0.001f;

	mouseXLastFrame = sf::Mouse::getPosition().x;
	mouseYLastFrame = sf::Mouse::getPosition().y;
}

glm::mat4 MyCamera::GetView(void)
{
	//temporary frame quaternion from pitch,yaw,roll 
	//here roll is not used
	glm::quat key_quat = glm::quat(glm::vec3(fPitch, fYaw, fRoll));
	//reset values
	fPitch = fYaw = fRoll = 0;

	//order matters,update camera_quat
	cam_quat = key_quat * cam_quat;
	cam_quat = glm::normalize(cam_quat);
	glm::mat4 rotate = glm::mat4_cast(cam_quat);
	
	//Rotate forward vec 
	/*glm::mat4 newForward = glm::mat4_cast(glm::quat(forward));
	newForward *= rotate;
	forward = glm::eulerAngles(glm::quat(newForward));
	forward = glm::normalize(forward);

	//Rotate up vec
	glm::mat4 newUp = glm::mat4_cast(glm::quat(up));
	newUp *= rotate;
	up = glm::eulerAngles(glm::quat(newUp));
	up = glm::normalize(up);

	//Rotate right vec
	glm::mat4 newRight = glm::mat4_cast(glm::quat(right));
	newRight *= rotate;
	right = glm::eulerAngles(glm::quat(newRight));
	right = glm::normalize(right);*/

	glm::mat4 translate = glm::mat4(1.0f);
	//translate = glm::translate(translate, -forward);
	translate = glm::translate(translate, position);
	viewMatrix = rotate * translate;
	
	forward = glm::vec3(viewMatrix[0][2], viewMatrix[1][2], viewMatrix[2][2]);
	right = glm::vec3(viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0]);
	up = glm::cross(forward, right);
	return viewMatrix;
}

glm::mat4 MyCamera::GetProjection(bool bOrtho)
{
	if (bOrtho) {
		return glm::ortho(-10.0f, 10.0f, -40.0f, 40.0f, 0.01f, 1000.0f);
	}
	else {
		return glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 1000.0f);
	}
}

void MyCamera::SetPosition(vector3 newPos)
{
	position = newPos;
}

vector3 MyCamera::GetPosition(void)
{
	return position;
}

void MyCamera::SetTarget(vector3 newTarget)
{
	target = newTarget;
}

void MyCamera::SetUp(vector3 newUp)
{
	up = newUp;
}

void MyCamera::MoveForward(float fIncrement)
{
	SetPosition((forward * fIncrement) + position);
	//SetPosition(glm::vec3(position.x, position.y, position.z + fIncrement));
}

void MyCamera::MoveSideways(float fIncrement)
{
	//SetPosition(glm::vec3(position.x + fIncrement, position.y, position.z));
	SetPosition((right * fIncrement) + position);
}

void MyCamera::MoveVertical(float fIncrement)
{
	//SetPosition(glm::vec3(position.x, position.y + fIncrement, position.z));
	SetPosition((up * fIncrement) + position);
}

void MyCamera::ChangePitch(float fDegree)
{
	fPitch += fDegree;

}

void MyCamera::ChangeRoll(float fDegree)
{
	fRoll += fDegree;
}

void MyCamera::ChangeYaw(float fDegree)
{
	fYaw += fDegree;
}


MyCamera::~MyCamera()
{
}
