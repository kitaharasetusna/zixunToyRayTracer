#include "lightPoint.hpp"

//default point light
myRT::LightPoint::LightPoint()
{
    m_color = qbVector<double> {std::vector<double> {1.0, 1.0, 1.0}};
    m_intensity = 1.0;
}

myRT::LightPoint::~LightPoint()
{
    
}

bool myRT::LightPoint::computeIllumination (const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                        const std::vector<std::shared_ptr<myRT::ObjectBase>> &objectList,
                                        const std::shared_ptr<myRT::ObjectBase> & currentObject,
                                        qbVector<double>&color, double &intensity)
{
    //mentioned inverse order(recall the picture: theta is the smaller one)
    qbVector<double> lightDir = (m_location-intPoint).Normalized();

    qbVector<double> startPoint = intPoint;


    //construct a right from poi to the light
    myRT::Ray lightRay (startPoint , startPoint + lightDir);
    qbVector<double> poi		{3};
	qbVector<double> poiNormal	{3};
	qbVector<double> poiColor	{3};
	bool validInt = false;

    for (auto sceneObject : objectList)
	{
		if (sceneObject != currentObject)
		{
			validInt = sceneObject ->TestIntersections(lightRay, poi, poiNormal, poiColor);
		}
		
		/* If we have an intersection, then there is no point checking further
			so we can break out of the loop. In other words, this object is
			blocking light from this light source. */
		if (validInt)
			break;
	}

    if(!validInt)
    {
         double nl =qbVector<double>::dot(localNormal, lightDir);
        intensity = m_intensity*(std::max(0.0, nl));
        if(nl<0)
        {
            color = m_color;
            return false;
        }
        else
        {
            
            color = m_color;
            return true; 
        }
        return true;
    }
    else
    {
        // Shadow, so no illumination.
		color = m_color;
		intensity = 0.0;
		return false;
    }
}