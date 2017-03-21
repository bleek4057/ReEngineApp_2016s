#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Assignment  06 - LERP"); // Window Name
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), ZERO_V3, REAXISY);

	// Color of the screen
	m_v4ClearColor = vector4(REBLACK, 1); // Set the clear color to black

	m_pMeshMngr->LoadModel("Sorted\\WallEye.bto", "WallEye");

	fDuration = 1.0f;

	//We will be changing fDuration based on the distance between points so we need to save the original
	origFDuration = fDuration;

	pointStartTime = 0;
	//Add points to the vector
	points = {
		vector3(-4.0f,-2.0f, 5.0f),
		vector3(1.0f,-2.0f, 5.0f),
		vector3(-3.0f,-1.0f, 3.0f),
		vector3(2.0f,-1.0f, 3.0f),
		vector3(-2.0f, 0.0f, 0.0f),
		vector3(3.0f, 0.0f, 0.0f),
		vector3(-1.0f, 1.0f,-3.0f),
		vector3(4.0f, 1.0f,-3.0f),
		vector3(0.0f, 2.0f,-5.0f),
		vector3(5.0f, 2.0f,-5.0f),
		vector3(1.0f, 3.0f,-5.0f)
	};

	//Starting off the object at the first point and setting up the second point
	currentPointNum = 0;
	nextPointNum = 1;

}

void AppClass::Update(void)
{
#pragma region Does not change anything here
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
#pragma region

#pragma region Does not need changes but feel free to change anything here
	//Lets us know how much time has passed since the last call
	double fTimeSpan = m_pSystem->LapClock(); //Delta time (between frame calls)

	//cumulative time
	static double fRunTime = 0.0f; //How much time has passed since the program started
	fRunTime += fTimeSpan; 
#pragma endregion

#pragma region Your Code goes here
	//How much time has elapsed between now and the start of our movement towards nextPoint
	pointElapsedTime = fRunTime - pointStartTime;

	//Telling the model what point it's coming from and what point it's going towards
	currentPoint = points[currentPointNum];
	nextPoint = points[nextPointNum];	

	//Find the distance between the two points. Scale fDuration up by that distance so points that are further apart take longer to traverse	
	/*float totalDist = glm::distance(currentPoint, nextPoint);
	fDuration = (totalDist / 3);*/

	//What percentage of the way has the model traveled	
	double percentToNextPoint = pointElapsedTime / fDuration;
	float mappedPercent = (float)MapValue(percentToNextPoint, 0.0, (double)fDuration, 0.0, 1.0);
	
	//Find the current position of the model by lerping between the current point and the next point based on the percent of the way we've travelled between the two points, mapped between 0 and 1
	currentPos = glm::lerp(currentPoint, nextPoint, mappedPercent);

	currentTransformMatrix = glm::translate(IDENTITY_M4, currentPos);
	
	if (pointElapsedTime >= fDuration) {
	//if(currentPos == nextPoint){
		currentPointNum++;
		nextPointNum++;

		pointStartTime = fRunTime;
		
		if (nextPointNum >= points.size()) {
			nextPointNum = 0;
		}

		if (currentPointNum >= points.size()) {
			currentPointNum = 0;
		}
	}

	m_pMeshMngr->SetModelMatrix(currentTransformMatrix, "WallEye");
#pragma endregion

#pragma region Does not need changes but feel free to change anything here
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
#pragma endregion
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	//Render the grid based on the camera's mode:
	m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}