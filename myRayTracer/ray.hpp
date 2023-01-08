#ifndef RAY_H
#define RAY_H
#include "./qbLinAlg/qbVector.h"
namespace myRT
{
    class Ray
    {
        public:
        //some functions  TODO: why &?
        Ray(qbVector<double> &startPoint, qbVector<double> &endPoint);

        qbVector<double> GetStartP() const;
        qbVector<double> GetEndP()   const;

        public:
        //some public variables
        qbVector<double> m_PointStart {3};
        qbVector<double> m_PointEnd   {3};
        qbVector<double> m_Ray   {3};

    };
}


#endif