#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include "./qbLinAlg/qbVector.h"
#include "ray.hpp"
//one for linear algebra
//the other for intersecting 

namespace  myRT
{
    class ObjectBase
    {
        public:
            ObjectBase();
            virtual ~ObjectBase();

        //TODO: set private

            //test wether castRay instersect with this object
            //use intPoint to get intersection point
            //use localNormal to get intersection normal
            //use localColor to get local color
            virtual bool TestIntersections(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double>);


            //TODO in next update
            bool CloseEnough(const double f1, const double f2);

        public:
            //color of the object
            qbVector<double> m_baseColor {3};

    };
} // namespace  myRT



#endif