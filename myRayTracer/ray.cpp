#include "ray.hpp"

myRT::Ray::Ray(qbVector<double> &startPoint, qbVector<double> &endPoint)
{
    m_PointStart = startPoint;
    m_PointEnd   =  endPoint;
    m_Ray        = endPoint-startPoint;
}

qbVector<double> myRT::Ray::GetStartP() const
{
    return m_PointStart;
}

qbVector<double> myRT::Ray::GetEndP() const
{
    return m_PointEnd;
}
