#include "camera.hpp"


myRT::Camera::Camera()
{
	// The default constructor.
	m_cameraPosition = qbVector<double>	{std::vector<double> {0.0, -10.0, 0.0}};
	m_cameraLookAt = qbVector<double> 	{std::vector<double> {0.0, 0.0, 0.0}};
	m_cameraUp = qbVector<double> 			{std::vector<double> {0.0, 0.0, 1.0}};
	m_cameraLength = 1.0;
	m_cameraHorzSize = 1.0;
	m_cameraAspectRatio = 1.0;
}


void myRT::Camera::SetCameraPosition(const qbVector<double> &newPosition)
{
	m_cameraPosition = newPosition;
}

void myRT::Camera::SetLookAtPosition(const qbVector<double> &newLookAt)
{
	m_cameraLookAt = newLookAt;
}

void myRT::Camera::SetUp(const qbVector<double> &upVector)
{
	m_cameraUp = upVector;
}

void myRT::Camera::SetLength(double newLength)
{
	m_cameraLength = newLength;
}

void myRT::Camera::SetHorzSize(double newHorzSize)
{
	m_cameraHorzSize = newHorzSize;
}

void myRT::Camera::SetAspect(double newAspect)
{
	m_cameraAspectRatio = newAspect;
}




qbVector<double> myRT::Camera::GetPosition()
{
    return m_cameraPosition;
}


qbVector<double> myRT::Camera::GetLookAt()
{
    return m_cameraLookAt;
}


qbVector<double> myRT::Camera::GetUp()
{
    return m_cameraUp;
}


double myRT::Camera::GetLength()
{
    return m_cameraLength;
}

double myRT::Camera::GetHorzSize()
{
	return m_cameraHorzSize;
}

double myRT::Camera::GetAspect()
{
	return m_cameraAspectRatio;
}

qbVector<double> myRT::Camera::GetU()
{
	return m_projectionScreenU;
}

qbVector<double> myRT::Camera::GetV()
{
	return m_projectionScreenV;
}

qbVector<double> myRT::Camera::GetScreenCentre()
{
	return m_projectionScreenCentre;
}

void myRT::Camera::UpdateCameraGeometry()
{
	//align can be computed by LooAt-CameraPo. Norm
	m_alignmentVector = m_cameraLookAt - m_cameraPosition;
	m_alignmentVector.Normalize();

    //center can be computed: center = CameraPos + align*Length 
	m_projectionScreenCentre = m_cameraPosition + (m_cameraLength * m_alignmentVector);
	
	//U can be computed: U=align X LookUp .Norm
    //V can be computed: V=U X align. Norm
	m_projectionScreenU = qbVector<double>::cross(m_alignmentVector, m_cameraUp);
	m_projectionScreenU.Normalize();
	m_projectionScreenV = qbVector<double>::cross(m_projectionScreenU, m_alignmentVector);
	m_projectionScreenV.Normalize();
	
	// Modify the U and V vectors to match the size and aspect ratio.
    //m_cameraHorzSize: length of 1 horizontal space
	m_projectionScreenU = m_projectionScreenU * m_cameraHorzSize;
	m_projectionScreenV = m_projectionScreenV * (m_cameraHorzSize / m_cameraAspectRatio);
}

bool myRT::Camera::GenerateRay(float proScreenX, float proScreenY, myRT::Ray &cameraRay)
{
	// Compute the location of the screen point in world coordinates.
	qbVector<double> screenWorldPart1 = m_projectionScreenCentre + (m_projectionScreenU * proScreenX);
	qbVector<double> screenWorldCoordinate = screenWorldPart1 + (m_projectionScreenV * proScreenY);
	

	//in order to write this , we have to make changes to ray.cpp and ray.hpp:
	// we need Ray();
	// Use this point along with the camera position to compute the ray.
	cameraRay.m_PointStart = m_cameraPosition;//member of camera(origin of the Coordinate)
	cameraRay.m_PointEnd = screenWorldCoordinate;
	cameraRay.m_Ray = screenWorldCoordinate-m_cameraPosition;
	return true;
}