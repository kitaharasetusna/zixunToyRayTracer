#include "materialSimple.hpp"

myRT::MaterialSimple::MaterialSimple()
{

}

myRT::MaterialSimple::~MaterialSimple()
{
    
}

qbVector<double> myRT::MaterialSimple::ComputeColor(const std::vector<std::shared_ptr<myRT::ObjectBase>> &objectList,
                                                  const std::vector<std::shared_ptr<myRT::LightBase>> &lightList,
                                                  const std::shared_ptr<myRT::ObjectBase> &curentObject,
                                                  const qbVector<double> &intPoint, const qbVector<double> &localNormal,
												  const myRT::Ray &cameraRay)
{
    qbVector<double> matColor	{3};
	qbVector<double> refColor   {3};
	qbVector<double> difColor	{3};
	qbVector<double> spcColor	{3};
    difColor = ComputeDiffuseColor(objectList, lightList, curentObject, intPoint, localNormal, m_baseColor);
    // Compute the reflection component.
	
	if(m_reflectivity>0.0)
		refColor = ComputeReflectionColor(objectList, lightList, curentObject, intPoint, localNormal, cameraRay);
	//recutrsive part
	matColor = (refColor * m_reflectivity) + (difColor * (1 - m_reflectivity));
	// Compute the specular component.
	if (m_shininess > 0.0)
		spcColor = ComputeSpecular(objectList, lightList, intPoint, localNormal, cameraRay);

    matColor = matColor + spcColor;
	return matColor;
}

qbVector<double> myRT::MaterialSimple::ComputeSpecular(const std::vector<std::shared_ptr<myRT::ObjectBase>> &objectList,
                                                  const std::vector<std::shared_ptr<myRT::LightBase>> &lightList,
                                                  const qbVector<double> &intPoint, const qbVector<double> &localNormal,
												  const myRT::Ray &cameraRay)
{
    qbVector<double> spcColor	{3};
	double red = 0.0;
	double green = 0.0;
	double blue = 0.0;
    for (auto currentLight : lightList)
	{
        double intensity = 0.0;
		
		// Construct a vector pointing from the intersection point to the light.
		qbVector<double> lightDir = (currentLight->m_location - intPoint).Normalized();
        // Compute a start point.
		qbVector<double> startPoint = intPoint + (lightDir * 0.001);
		
		// Construct a ray from the point of intersection to the light.
		myRT::Ray lightRay (startPoint, startPoint + lightDir);
		
		/* Loop through all objects in the scene to check if any
			obstruct light from this source. */
		qbVector<double> poi				{3};
		qbVector<double> poiNormal	        {3};
		qbVector<double> poiColor		    {3};
		bool validInt = false;
        for (auto sceneObject : objectList)
		{
			validInt = sceneObject ->TestIntersections(lightRay, poi, poiNormal, poiColor);
			if (validInt)
				break;
		}
        /* If no intersections were found, then proceed with
			computing the specular component. */
		if (!validInt)
		{
			// Compute the reflection vector.
			qbVector<double> d = lightRay.m_Ray;
			qbVector<double> r = d - (2 * qbVector<double>::dot(d, localNormal) * localNormal);
			r.Normalize();
			
			// Compute the dot product.
			qbVector<double> v = cameraRay.m_Ray;
			v.Normalize();
			double dotProduct = qbVector<double>::dot(r, v);
			
			// Only proceed if the dot product is positive.
			if (dotProduct > 0.0)
			{
				intensity = m_reflectivity * std::pow(dotProduct, m_shininess);
			}
		}
        red += currentLight->m_color.GetElement(0) * intensity;
        green += currentLight->m_color.GetElement(1) * intensity;
        blue += currentLight->m_color.GetElement(2) * intensity;
    }
    spcColor.SetElement(0, red);
    spcColor.SetElement(1, green);
    spcColor.SetElement(2, blue);
    return spcColor;
}