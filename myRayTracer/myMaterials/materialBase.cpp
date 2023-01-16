#include "materialBase.hpp"

myRT::MaterialBase::MaterialBase()
{

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