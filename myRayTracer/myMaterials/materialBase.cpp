#include "materialBase.hpp"

myRT::MaterialBase::MaterialBase()
{
    m_maxReflectionRays = 3;
	m_reflectionRayCount = 0;
}
myRT::MaterialBase::~MaterialBase()
{
    
}

qbVector<double> myRT::MaterialBase::ComputeColor(const std::vector<std::shared_ptr<myRT::ObjectBase>> &objectList,
                                                  const std::vector<std::shared_ptr<myRT::LightBase>> &lightList,
                                                  const std::shared_ptr<myRT::ObjectBase> &curentObject,
                                                  const qbVector<double> &intPoint, const qbVector<double> &localNormal,
												  const myRT::Ray &cameraRay)
{
    // Define an initial material color.
	qbVector<double> matColor	{3};
	
	return matColor;
}

//we set this static because this has nothing to do with the material itself
qbVector<double> myRT::MaterialBase::ComputeDiffuseColor(const std::vector<std::shared_ptr<myRT::ObjectBase>> &objectList,
                                                  const std::vector<std::shared_ptr<myRT::LightBase>> &lightList,
                                                  const std::shared_ptr<myRT::ObjectBase> &curentObject,
                                                  const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                                  const qbVector<double> &baseColor)
{
    qbVector<double> diffuseColor	{3};
    double intensity;
    qbVector<double> color {3};
    double red = 0.0;
    double green = 0.0;
    double blue = 0.0;
    bool validIllum = false;
    bool illumFound = false;
    for (auto currentLight : lightList)
    {
        validIllum = currentLight ->computeIllumination(intPoint, localNormal, objectList, curentObject, color, intensity);
        if (validIllum)
        {
            illumFound = true;
            red += color.GetElement(0) * intensity;
            green += color.GetElement(1) * intensity;
            blue += color.GetElement(2) * intensity;
        }
    }
    //light_color(color)*intensity(n*l)*objectcolor(c_r)
    if (illumFound)
    {
        diffuseColor.SetElement(0, red * baseColor.GetElement(0));
		diffuseColor.SetElement(1, green * baseColor.GetElement(1));
		diffuseColor.SetElement(2, blue * baseColor.GetElement(2));

    }
    return diffuseColor;
}

//fun to compute color ac to reflection
qbVector<double> myRT::MaterialBase::ComputeReflectionColor(const std::vector<std::shared_ptr<myRT::ObjectBase>> &objectList,
                                                  const std::vector<std::shared_ptr<myRT::LightBase>> &lightList,
                                                  const std::shared_ptr<myRT::ObjectBase> &curentObject,
                                                  const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                                  const myRT::Ray &incidentRay)
{
    //color value to reutrn
    qbVector<double> reflectionColor {3};

    // Compute the reflection vector.
	qbVector<double>  d = incidentRay.m_Ray;
    //reflection value r=l-2(l*n)*n    r1=l-2*(l*n1)*n1; r2 = r1-2*(r1*n2)*n2
    qbVector<double> reflectionVector = d-2*qbVector<double>::dot(d, localNormal)*localNormal;
    myRT::Ray reflectionRay (intPoint, intPoint + reflectionVector);

    
   //cast this ray into the scene to find the closet object intersecting with this ray
    std::shared_ptr<myRT::ObjectBase> closestObject;
    qbVector<double> closestIntPoint		{3};
	qbVector<double> closestLocalNormal		{3};
	qbVector<double> closestLocalColor		{3};

    //get closetIntersected Object
    bool intersectionFound = CastRay(reflectionRay, objectList, curentObject, closestObject, closestIntPoint, closestLocalNormal, closestLocalColor);
    
	qbVector<double> matColor	{3};

    //bouncing time <maxReflectionRays
    if ((intersectionFound) && (m_reflectionRayCount < m_maxReflectionRays))
	{
        //increase the count
        m_reflectionRayCount++;
        // Check if a material has been assigned.
		if (closestObject -> m_hasMaterial)
		{
            //recursive part
			// Use the material to compute the color.
            //incident ray = refelction ray
			matColor = closestObject -> m_pMaterial -> ComputeColor(objectList, lightList, closestObject, closestIntPoint, closestLocalNormal, reflectionRay);
        }
        else
		{
			matColor = myRT::MaterialBase::ComputeDiffuseColor(objectList, lightList, closestObject, closestIntPoint, closestLocalNormal, closestObject->m_baseColor);
		}
	}
	else
	{
		// Leave matColor as it is.
	}
	
	reflectionColor = matColor;
	return reflectionColor;
}



//return the closet intersection 
bool  myRT::MaterialBase::CastRay(const myRT::Ray &castRay, const std::vector<std::shared_ptr< myRT::ObjectBase>> &objectList,
			const std::shared_ptr< myRT::ObjectBase> &thisObject,
			std::shared_ptr<myRT::ObjectBase> &closestObject,
			qbVector<double> &closestIntPoint, qbVector<double> &closestLocalNormal,
			qbVector<double> &closestLocalColor)
{
    qbVector<double> intPoint		{3};
	qbVector<double> localNormal	{3};
	qbVector<double> localColor		{3};

    double minDist = 1e6;
	bool intersectionFound = false;
    for (auto currentObject : objectList)
	{
		if (currentObject != thisObject)
		{
			bool validInt = currentObject ->TestIntersections(castRay, intPoint, localNormal, localColor);
			
			// If we have a valid intersection.
			if (validInt)
			{
				// Set the flag to show that we found an intersection.
				intersectionFound = true;
				
				// Compute the distance between the source and the intersection point.
				double dist = (intPoint - castRay.m_PointStart).norm();
				
				// Store a reference to this object if it is the closest.
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
	}
	
	return intersectionFound;
}