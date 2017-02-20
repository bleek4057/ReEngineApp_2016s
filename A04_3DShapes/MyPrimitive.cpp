#include "MyPrimitive.h"
MyPrimitive::MyPrimitive() { }
MyPrimitive::MyPrimitive(const MyPrimitive& other) { }
MyPrimitive& MyPrimitive::operator=(const MyPrimitive& other) { return *this; }
MyPrimitive::~MyPrimitive(void) { super::Release(); }
void MyPrimitive::CompileObject(vector3 a_v3Color)
{
	m_uVertexCount = static_cast<int> (m_lVertexPos.size());
	for (uint i = 0; i < m_uVertexCount; i++)
	{
		AddVertexColor(a_v3Color);
	}
	
	CompleteTriangleInfo(true);
	CompileOpenGL3X();

}
//C--D
//|\ |
//| \|
//A--B
//This will make the triang A->B->C and then the triang C->B->D
void MyPrimitive::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

	AddVertexPosition(a_vTopLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopRight);
}
void MyPrimitive::GeneratePlane(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;

	vector3 pointA(-fValue, -fValue, 0.0f); //0
	vector3 pointB(fValue, -fValue, 0.0f); //1
	vector3 pointC(fValue, fValue, 0.0f); //2
	vector3 pointD(-fValue, fValue, 0.0f); //3

	vector3 pointE(fValue, -fValue, -0.001f); //1
	vector3 pointF(-fValue, -fValue, -0.001f); //0
	vector3 pointG(fValue, fValue, -0.001f); //2
	vector3 pointH(-fValue, fValue, -0.001f); //3

											  //F
	AddQuad(pointA, pointB, pointD, pointC);
	//Double sided
	AddQuad(pointE, pointF, pointG, pointH);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue, -fValue, -fValue); //4
	vector3 point5(fValue, -fValue, -fValue); //5
	vector3 point6(fValue, fValue, -fValue); //6
	vector3 point7(-fValue, fValue, -fValue); //7

											  //F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1
	
	
	/*vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	AddQuad(point0, point1, point3, point2);*/

	float _sin = 0;
	float _cos = 0;

	float _cos2 = 0;
	float _sin2 = 0;


	for (int i = 0; i < a_nSubdivisions; ++i) {
		float currentAngle = ((float)(PI * 2) * ((float)i / a_nSubdivisions));
		float nextAngle = ((float)(PI * 2) * ((float)(i+1) / a_nSubdivisions));

		//std::cout << "i: " << i << ", Subs: " << a_nSubdivisions << std::endl;
		//std::cout << "Current Angle: " << currentAngle << std::endl;
		
		_sin = a_fRadius * sin(currentAngle);
		_cos = a_fRadius * cos(currentAngle);

		_sin2 = a_fRadius * sin(nextAngle);
		_cos2 = a_fRadius * cos(nextAngle);

		//Creating the base here
		vector3 point0(_sin, _cos, 0);
		vector3 point1(0, 0, 0);
		vector3 point2(_sin2, _cos2, 0);
		vector3 point3(_sin, _cos, 0);

		AddQuad(point0, point1, point2, point3);

		//Creating the upright here
		vector3 point4(0, 0, a_fHeight);

		AddQuad(point0, point4, point2, point3);
	}

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1

	float _sin = 0;
	float _cos = 0;

	float _cos2 = 0;
	float _sin2 = 0;

	//Creating the base
	for (int i = 0; i < a_nSubdivisions; ++i) {
		float currentAngle = ((float)(PI * 2) * ((float)i / a_nSubdivisions));
		float nextAngle = ((float)(PI * 2) * ((float)(i + 1) / a_nSubdivisions));

		//std::cout << "i: " << i << ", Subs: " << a_nSubdivisions << std::endl;
		//std::cout << "Current Angle: " << currentAngle << std::endl;

		_sin = a_fRadius * sin(currentAngle);
		_cos = a_fRadius * cos(currentAngle);

		_sin2 = a_fRadius * sin(nextAngle);
		_cos2 = a_fRadius * cos(nextAngle);

		//Creating the base here
		vector3 point0(_sin, _cos, 0);
		vector3 point1(0, 0, 0);
		vector3 point2(_sin2, _cos2, 0);
		vector3 point3(_sin, _cos, 0);

		AddQuad(point0, point1, point2, point3);
	}

	//Creating the cap
	for (int i = 0; i < a_nSubdivisions; ++i) {
		float currentAngle = ((float)(PI * 2) * ((float)i / a_nSubdivisions));
		float nextAngle = ((float)(PI * 2) * ((float)(i + 1) / a_nSubdivisions));

		//std::cout << "i: " << i << ", Subs: " << a_nSubdivisions << std::endl;
		//std::cout << "Current Angle: " << currentAngle << std::endl;

		_sin = a_fRadius * sin(currentAngle);
		_cos = a_fRadius * cos(currentAngle);

		_sin2 = a_fRadius * sin(nextAngle);
		_cos2 = a_fRadius * cos(nextAngle);

		vector3 point0(_sin, _cos, a_fHeight);
		vector3 point1(0, 0, a_fHeight);
		vector3 point2(_sin2, _cos2, a_fHeight);
		vector3 point3(_sin, _cos, a_fHeight);

		AddQuad(point0, point1, point2, point3);

		//Creating the uprights here
		vector3 point4(_sin, _cos, 0);
		vector3 point5(_sin2, _cos2, 0);

		AddQuad(point0, point2, point4, point5);
	}

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	
	float _sin = 0;
	float _cos = 0;

	float _cos2 = 0;
	float _sin2 = 0;

	float _innerCos = 0;
	float _innerSin = 0;

	float _innerCos2 = 0;
	float _innerSin2 = 0;

	//Creating the base
	for (int i = 0; i < a_nSubdivisions; ++i) {
		float currentAngle = ((float)(PI * 2) * ((float)i / a_nSubdivisions));
		float nextAngle = ((float)(PI * 2) * ((float)(i + 1) / a_nSubdivisions));

		//Creating the outer ring
		_sin = a_fOuterRadius * sin(currentAngle);
		_cos = a_fOuterRadius * cos(currentAngle);

		_sin2 = a_fOuterRadius * sin(nextAngle);
		_cos2 = a_fOuterRadius * cos(nextAngle);


		//Creating the inner ring
		_innerSin = a_fInnerRadius * sin(currentAngle);
		_innerCos = a_fInnerRadius * cos(currentAngle);

		_innerSin2 = a_fInnerRadius * sin(nextAngle);
		_innerCos2 = a_fInnerRadius * cos(nextAngle);

		//Creating the base here
		vector3 point0(_sin, _cos, 0);
		vector3 point1(_innerSin, _innerCos, 0);
		vector3 point2(_innerSin2, _innerCos2, 0);
		vector3 point3(_sin2, _cos2, 0);

		AddQuad(point3, point2, point0, point1);
	}

	//Creating the cap
	for (int i = 0; i < a_nSubdivisions; ++i) {
		float currentAngle = ((float)(PI * 2) * ((float)i / a_nSubdivisions));
		float nextAngle = ((float)(PI * 2) * ((float)(i + 1) / a_nSubdivisions));

		//Creating the outer ring
		_sin = a_fOuterRadius * sin(currentAngle);
		_cos = a_fOuterRadius * cos(currentAngle);

		_sin2 = a_fOuterRadius * sin(nextAngle);
		_cos2 = a_fOuterRadius * cos(nextAngle);


		//Creating the inner ring
		_innerSin = a_fInnerRadius * sin(currentAngle);
		_innerCos = a_fInnerRadius * cos(currentAngle);

		_innerSin2 = a_fInnerRadius * sin(nextAngle);
		_innerCos2 = a_fInnerRadius * cos(nextAngle);

		//Creating the base here
		vector3 point0(_sin, _cos, a_fHeight);
		vector3 point1(_innerSin, _innerCos, a_fHeight);
		vector3 point2(_innerSin2, _innerCos2, a_fHeight);
		vector3 point3(_sin2, _cos2, a_fHeight);

		AddQuad(point0, point1, point3, point2);

		//Adding the outer shell
		vector3 point4(_sin, _cos, 0);
		vector3 point5(_sin2, _cos2, 0);

		AddQuad(point3, point5, point0, point4);

		//Adding the inner shell
		vector3 point6(_innerSin, _innerCos, 0);
		vector3 point7(_innerSin2, _innerCos2, 0);

		AddQuad(point1, point6, point2, point7);
	}
	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	if (a_fOuterRadius <= a_fInnerRadius + 0.1f)
		return;

	if (a_nSubdivisionsA < 3)
		a_nSubdivisionsA = 3;
	if (a_nSubdivisionsA > 25)
		a_nSubdivisionsA = 25;

	if (a_nSubdivisionsB < 3)
		a_nSubdivisionsB = 3;
	if (a_nSubdivisionsB > 25)
		a_nSubdivisionsB = 25;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	AddQuad(point0, point1, point3, point2);

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	//Attempting to build a sphere by stacking cylinders on top of each other
	//Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2, a_v3Color);
		return;
	}
	if (a_nSubdivisions > 6)
		a_nSubdivisions = 6;
	if (a_nSubdivisions %2 == 0) {
		a_nSubdivisions++;
	}

	Release();
	Init();
	
	float medianRingNum = a_nSubdivisions / 2;
	float ringZ = 0;
	float ringHeight = 0;

	for (int j = 0; j < a_nSubdivisions; ++j) {
		float _sin = 0;
		float _cos = 0;

		float _cos2 = 0;
		float _sin2 = 0;
	
		float ringRadius = 1 / abs(j - medianRingNum) * a_fRadius;
		
		ringHeight = 0.5f;
		ringZ = ringZ + ringHeight;
		
		//Creating the base
		for (int i = 0; i < a_nSubdivisions; ++i) {
			float currentAngle = ((float)(PI * 2) * ((float)i / a_nSubdivisions));
			float nextAngle = ((float)(PI * 2) * ((float)(i + 1) / a_nSubdivisions));

			_sin = ringRadius * sin(currentAngle);
			_cos = ringRadius * cos(currentAngle);

			_sin2 = ringRadius * sin(nextAngle);
			_cos2 = ringRadius * cos(nextAngle);

			//Creating the base here
			vector3 point0(_sin, _cos, ringZ);
			vector3 point1(0, 0, ringZ);
			vector3 point2(_sin2, _cos2, ringZ);
			vector3 point3(_sin, _cos, ringZ);

			AddQuad(point0, point1, point2, point3);
		}

		//Creating the cap
		for (int i = 0; i < a_nSubdivisions; ++i) {
			float currentAngle = ((float)(PI * 2) * ((float)i / a_nSubdivisions));
			float nextAngle = ((float)(PI * 2) * ((float)(i + 1) / a_nSubdivisions));

			//std::cout << "i: " << i << ", Subs: " << a_nSubdivisions << std::endl;
			//std::cout << "Current Angle: " << currentAngle << std::endl;

			_sin = ringRadius * sin(currentAngle);
			_cos = ringRadius * cos(currentAngle);

			_sin2 = ringRadius * sin(nextAngle);
			_cos2 = ringRadius * cos(nextAngle);

			vector3 point0(_sin, _cos, ringZ + ringHeight);
			vector3 point1(0, 0, ringZ + ringHeight);
			vector3 point2(_sin2, _cos2, ringZ + ringHeight);
			vector3 point3(_sin, _cos, ringZ + ringHeight);

			AddQuad(point0, point1, point2, point3);

			//Creating the uprights here
			vector3 point4(_sin, _cos, ringZ);
			vector3 point5(_sin2, _cos2, ringZ);

			AddQuad(point0, point2, point4, point5);
		}
	}

	CompileObject(a_v3Color);
}