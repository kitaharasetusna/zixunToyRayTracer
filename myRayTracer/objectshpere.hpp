#ifndef OBJECTSHERE_H
#define OBJECTSHERE_H

#include "objectBase.hpp"

namespace myRT
{
    class ObjectShpere:public ObjectBase
    {
        public:
        //some functions to override
            ObjectShpere();
            
            virtual ~ObjectShpere() override;

            virtual bool TestIntersections(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double>) override;
    };
}

#endif