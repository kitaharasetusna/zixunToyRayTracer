#include "scene.hpp"

myRT::Scene::Scene()
{
    m_camera.SetCameraPosition(	qbVector<double>{std::vector<double> {0.0, -10.0, -2.0}} );
	m_camera.SetLookAtPosition	( qbVector<double>{std::vector<double> {0.0, 0.0, 0.0}} );
	m_camera.SetUp			( qbVector<double>{std::vector<double> {0.0, 0.0, 1.0}} );
	m_camera.SetHorzSize(0.25);
	m_camera.SetAspect(16.0 / 9.0);
	m_camera.UpdateCameraGeometry();

    //initialize the objectList
    m_objectList.push_back(std::make_shared<myRT::ObjectShpere>(myRT::ObjectShpere()));
    m_objectList.push_back(std::make_shared<myRT::ObjectShpere>(myRT::ObjectShpere()));
    m_objectList.push_back(std::make_shared<myRT::ObjectShpere>(myRT::ObjectShpere()));


    m_objectList.push_back(std::make_shared<myRT::ObjectPlane>(myRT::ObjectPlane()));
    m_objectList.at(3)->m_baseColor = qbVector<double>{std::vector<double> {0.5, 0.5, 0.5}};

    myRT::GTform planeMatrix;
    planeMatrix.SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0, 0.75}},
                            qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
                            qbVector<double>{std::vector<double>{4.0, 4.0, 1.0}});
    m_objectList.at(3) ->SetTransformMatirx(planeMatrix);


    //set all transforms
    //translation-rotation-scale
    myRT::GTform testMatrix1, testMatrix2, testMatrix3;
    testMatrix1.SetTransform(	qbVector<double>{std::vector<double>{-1.5, 0.0, 0.0}},
					qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
					qbVector<double>{std::vector<double>{0.5, 0.5, 0.75}});
														
	testMatrix2.SetTransform(	qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
					qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
					qbVector<double>{std::vector<double>{0.75, 0.5, 0.5}});
														
	testMatrix3.SetTransform(	qbVector<double>{std::vector<double>{1.5, 0.0, 0.0}},
					qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
					qbVector<double>{std::vector<double>{0.75, 0.5, 0.5}});
    m_objectList.at(0) -> SetTransformMatirx(testMatrix1);
	m_objectList.at(1) -> SetTransformMatirx(testMatrix2);
	m_objectList.at(2) -> SetTransformMatirx(testMatrix3);

    //set colors of objects
    m_objectList.at(0) -> m_baseColor = qbVector<double>{std::vector<double>{0.25, 0.5, 0.8}};
	m_objectList.at(1) -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 0.5, 0.0}};
	m_objectList.at(2) -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 0.8, 0.0}};

    //initialize the light

    // Construct a test light.

    //blue light
	m_lightList.push_back(std::make_shared<myRT::LightPoint> (myRT::LightPoint()));
	m_lightList.at(0) -> m_location = qbVector<double> {std::vector<double> {5.0, -10.0, -5.0}};
	m_lightList.at(0) -> m_color = qbVector<double> {std::vector<double> {0.0, 0.0, 1.0}};
	
    //red light
	m_lightList.push_back(std::make_shared<myRT::LightPoint> (myRT::LightPoint()));
	m_lightList.at(1) -> m_location = qbVector<double> {std::vector<double> {-5.0, -10.0, -5.0}};
	m_lightList.at(1) -> m_color = qbVector<double> {std::vector<double> {1.0, 0.0, 0.0}};
	
    //green light
	m_lightList.push_back(std::make_shared<myRT::LightPoint> (myRT::LightPoint()));
	m_lightList.at(2) -> m_location = qbVector<double> {std::vector<double> {0.0, -10.0, -5.0}};
	m_lightList.at(2) -> m_color = qbVector<double> {std::vector<double> {1.0, 1.0, 1.0}};
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


            //painter algorithm
            std::shared_ptr<myRT::ObjectBase> closestObject;
			qbVector<double> closestIntPoint	{3};
			qbVector<double> closestLocalNormal	{3};
			qbVector<double> closestLocalColor	{3};
            double minDist = 1e6;
			bool intersectionFound = false;
                //enumerate all objects to test intersection
                for(auto currentObject :m_objectList)
                {
                    bool validInt = currentObject->TestIntersections(cameraRay, intPoint, localNormal, localColor);
                    // Generate the ray for this pixel.
                    
                    if (validInt)
                    {
                        //set the intesection flag true
                        intersectionFound = true;

                        // Compute the distance between the camera and the point of intersection.
					    double dist = (intPoint - cameraRay.m_PointStart).norm();
                        // record the nearest point, normal and color
                        if (dist < minDist)
                        {
                            minDist = dist;
                            closestObject = currentObject;
                            closestIntPoint = intPoint;
                            closestLocalNormal = localNormal;
                            closestLocalColor = localColor;
                        }

                    }
                }
                // Compute the illumination
                if (intersectionFound)
                {
                    // Compute the intensity of illumination.
				    double intensity;
                    qbVector<double> color {3};
                    double red = 0.0;
                    double green = 0.0;
                    double blue = 0.0;
                    bool validIllum = false;
                    bool illumFound = false;
                    for (auto currentLight : m_lightList)
                    {
                        validIllum = currentLight ->computeIllumination(closestIntPoint, closestLocalNormal, m_objectList, closestObject, color, intensity);
                        if (validIllum)
                        {
                            illumFound = true;
                            red += color.GetElement(0) * intensity;
                            green += color.GetElement(1) * intensity;
                            blue += color.GetElement(2) * intensity;
                        }
                        //light_color(color)*intensity(n*l)*objectcolor(c_r)
                        if (illumFound)
                        {
                            red *= closestLocalColor.GetElement(0);
                            green *= closestLocalColor.GetElement(1);
                            blue *= closestLocalColor.GetElement(2);
                            image.SetPixel(i, j, red, green, blue);
                        }
                    }
                }
            }
    return true;
}