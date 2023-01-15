#ifndef OBJECTPLANE_H
#define OBJECTPLANE_H

#include "objectBase.hpp"

namespace myRT
{
    class ObjectPlane: public ObjectBase
    {
        public:
            ObjectPlane();
            virtual ~ObjectPlane() override;
            virtual bool TestIntersections(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor) override;
        private:
            //TODO
    };
} 



#endif