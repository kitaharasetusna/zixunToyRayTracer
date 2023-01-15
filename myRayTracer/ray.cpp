#include "ray.hpp"

myRT::Ray::Ray()
{
    m_PointStart = qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}};
    m_PointEnd = qbVector<double>{std::vector<double>{0.0, 0.0, 1.0}};
    m_Ray = m_PointEnd-m_PointStart;
}

myRT::Ray::Ray(const qbVector<double> &startPoint, const qbVector<double> &endPoint)
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
