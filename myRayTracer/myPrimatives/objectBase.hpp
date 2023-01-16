#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include <memory>
#include "../qbLinAlg/qbVector.h"
#include "../ray.hpp"
#include "../gtform.hpp"
//one for linear algebra
//the other for intersecting 
//for transformations

namespace  myRT
{
    //trick here: forward declared material, which will be overide
    class MaterialBase;
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
            virtual bool TestIntersections(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor);


            //TODO in next update
            bool CloseEnough(const double f1, const double f2);

            void SetTransformMatirx(const myRT::GTform &transformMatrix);

            bool assignMaterial(const std::shared_ptr<myRT::MaterialBase> &objectMaterial);

        public:
            //color of the object
            qbVector<double> m_baseColor {3};

            myRT::GTform m_transformationMatrix;

            std::shared_ptr<myRT::MaterialBase> m_pMaterial;

            bool m_hasMaterial = false;

    };
} // namespace  myRT



#endif