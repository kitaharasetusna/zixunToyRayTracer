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

    double nl =qbVector<double>::dot(localNormal, lightDir);
    //double angle = acos(qbVector<double>::dot(localNormal, lightDir));


    intensity = m_intensity*(std::max(0.0, nl));
    // //pi/2 if angle>pi/2->then we can't see it
    // if(angle>1.5708)
    // {
    //     color = m_color;
    //     intensity = 0.0;
    //     return false;
    // }
    // else
    // {
    //     color = m_color;
    //     intensity = m_intensity*(1.0-(angle/1.5708));
    //     return true;
    // }
}