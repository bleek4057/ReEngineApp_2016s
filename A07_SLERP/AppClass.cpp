#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("SLERP - JOHN MILLER"); // Window Name

	//Setting the color to black
	m_v4ClearColor = vector4(0.0f);
}

void AppClass::InitVariables(void)
{
	//Setting the position in which the camera is looking and its interest point
	m_pCameraMngr->SetPositionTargetAndView(vector3(12.12f, 28.52f, 11.34f), ZERO_V3, REAXISY);

	//Setting the color to black
	m_v4ClearColor = vector4(0.0f);

	//Loading the models
	m_pMeshMngr->LoadModel("Planets\\00_Sun.obj", "Sun");
	m_pMeshMngr->LoadModel("Planets\\03_Earth.obj", "Earth");
	m_pMeshMngr->LoadModel("Planets\\03A_Moon.obj", "Moon");

	//Setting the days duration
	m_fDay = 1.0f;
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	//Getting the time between calls
	double fCallTime = m_pSystem->LapClock();
	//Counting the cumulative time
	static double fRunTime = 0.0f;
	fRunTime += fCallTime;

	//Earth Orbit
	double fEarthHalfOrbTime = 182.5f * m_fDay; //Earths orbit around the sun lasts 365 days / half the time for 2 stops
	float fEarthHalfRevTime = 0.5f * m_fDay; // Move for Half a day
	float fMoonHalfOrbTime = 14.0f * m_fDay; //Moon's orbit is 28 earth days, so half the time for half a route

	//Keeping track of times

	currentEarthOrbitTime += (float)fCallTime;
	currentMoonOrbitTime += (float)fCallTime;

	if (currentEarthOrbitTime >= fEarthHalfOrbTime / 2) {
		currentEarthOrbitTime = 0;
	}
	
	currentMoonOrbitTime += (float)fCallTime;
	if (currentMoonOrbitTime >= fMoonHalfOrbTime / 2) {
		currentMoonOrbitTime = 0;
	}


	std::cout << currentEarthOrbitTime << "/" << fEarthHalfOrbTime << "=" << currentEarthOrbitTime / (fEarthHalfOrbTime) << std::endl;	
	


	//Revolve earth around its axis
	earthRevolutionStartQuat = glm::quat(vector3(0.0f, 0.0f, 0.0f));
	earthRevolutionEndQuat = glm::quat(vector3(0.0f, 0.0f, 180.0f));

	float earthPercentRevolved = currentEarthOrbitTime / (fEarthHalfRevTime);
	newEarthRevolutionQuat = glm::mix(earthRevolutionStartQuat, earthRevolutionEndQuat, earthPercentRevolved);


	matrix4 earthRotMat = glm::mat4_cast(newEarthRevolutionQuat);

	m4Earth *= earthRotMat;


	//Move the models
	m4Earth = glm::translate(IDENTITY_M4, vector3(11.0f, 0.0f, 0.0f));
	

	//Rotate earth around the sun
	earthOrbitStartQuat = glm::quat(vector3(0.0f, 0.0f, 0.0f));
	earthOrbitEndQuat = glm::quat(vector3(0.0f, 0.0f, 180.0f));

	float earthPercentOrbited = currentEarthOrbitTime / (fEarthHalfOrbTime);
	newEarthOrbitQuat = glm::mix(earthOrbitStartQuat, earthOrbitEndQuat, earthPercentOrbited);


	matrix4 earthOrbit = glm::mat4_cast(newEarthOrbitQuat);

	m4Earth *= earthOrbit;


	//Orbit the moon around the earth
	moonOrbitStartQuat = glm::quat(vector3(0.0f, 0.0f, 0.0f));
	moonOrbitEndQuat = glm::quat(vector3(0.0f, 0.0f, 180.0f));

	float moonPercentOrbited = currentMoonOrbitTime / (fMoonHalfOrbTime);
	newEarthOrbitQuat = glm::mix(moonOrbitStartQuat, moonOrbitEndQuat, moonPercentOrbited);


	matrix4 moonOrbit = glm::mat4_cast(newEarthOrbitQuat);

	m4Moon *= moonOrbit;


	//Move the moon models
	m4Moon = glm::translate(m4Earth, vector3(2.0f, 0.0f, 0.0f));

	//Scale the models
	m4Sun = glm::scale(IDENTITY_M4, vector3(5.936f, 5.936f, 5.936f));
	m4Earth = glm::scale(m4Earth, vector3(0.524f, 0.524f, 0.524f));
	m4Moon = glm::scale(m4Moon, vector3(0.27f, 0.27f, 0.27f));


	//Setting the matrices
	m_pMeshMngr->SetModelMatrix(m4Sun, "Sun");
	m_pMeshMngr->SetModelMatrix(m4Earth, "Earth");
	m_pMeshMngr->SetModelMatrix(m4Moon, "Moon");

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	static int nEarthOrbits = 0;
	static int nEarthRevolutions = 0;
	static int nMoonOrbits = 0;


	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	
	m_pMeshMngr->Print("Time:");
	m_pMeshMngr->PrintLine(std::to_string(fRunTime));

	m_pMeshMngr->Print("Day:");
	m_pMeshMngr->PrintLine(std::to_string(m_fDay));

	m_pMeshMngr->Print("E_Orbits:");
	m_pMeshMngr->PrintLine(std::to_string(nEarthOrbits));

	m_pMeshMngr->Print("E_Revolutions:");
	m_pMeshMngr->PrintLine(std::to_string(nEarthRevolutions));

	m_pMeshMngr->Print("M_Orbits:");
	m_pMeshMngr->PrintLine(std::to_string(nMoonOrbits));

	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
	{
	default:
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	}
	
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}