#include "scene.hpp"

myRT::Scene::Scene()
{
    m_camera.SetCameraPosition(	qbVector<double>{std::vector<double> {0.0, -10.0, 0.0}} );
	m_camera.SetLookAtPosition	( qbVector<double>{std::vector<double> {0.0, 0.0, 0.0}} );
	m_camera.SetUp			( qbVector<double>{std::vector<double> {0.0, 0.0, 1.0}} );
	m_camera.SetHorzSize(0.25);
	m_camera.SetAspect(16.0 / 9.0);
	m_camera.UpdateCameraGeometry();
}


bool myRT::Scene::Render(Image &image)
{
    int m_xSize = image.GetXSize();
    int m_ySize = image.GetYSize();
    //some info // Loop over each pixel in our image.
	myRT::Ray cameraRay;
	qbVector<double> intPoint	    (3);
	qbVector<double> localNormal	(3);
	qbVector<double> localColor		(3);
    //scalar factor to scale pics [0,2]
    double xFact = 1.0 / (static_cast<double>(m_xSize) / 2.0);
	double yFact = 1.0 / (static_cast<double>(m_ySize) / 2.0);
	double minDist = 1e6;
	double maxDist = 0.0;
    //get gradient color
    for(int i=0; i<m_xSize; i++)
        for(int j=0; j<m_ySize; j++)
            {
                double normX = (static_cast<double>(i) * xFact) - 1.0;
                double normY = (static_cast<double>(j) * yFact) - 1.0;
                m_camera.GenerateRay(normX, normY, cameraRay);

                bool validInt = m_testSphere.TestIntersections(cameraRay, intPoint, localNormal, localColor);
                // Generate the ray for this pixel.
			    m_camera.GenerateRay(normX, normY, cameraRay);
                if (validInt)
                {
                    //get dist from camre to the sphere
                    double dist = (intPoint - cameraRay.m_PointStart).norm();
                    //update distance(max min, kinda of dp)
                    if (dist > maxDist)
					maxDist = dist;
				
				    if (dist < minDist)
					minDist = dist;
                    //set the color of shpere
                    //image.SetPixel(i, j, 255.0, 0.0, 0.0);
                    image.SetPixel(i, j, 255.0 - ((dist - 9.0) / 0.94605) * 255.0, 0.0, 0.0);
                }
                else
                {
                    //set black
                    image.SetPixel(i, j, 0.0, 0.0, 0.0);
                }
            }
    return true;
}