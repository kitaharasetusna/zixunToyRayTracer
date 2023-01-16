#include "objectBase.hpp"
#include<math.h>

#define EPSILON 1e-21f;

myRT::ObjectBase::ObjectBase()
{

}

myRT::ObjectBase::~ObjectBase()
{

}

bool myRT::ObjectBase::TestIntersections(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor)
{
    return false;
}

//TODO
bool myRT::ObjectBase::CloseEnough(const double f1, const double f2)
{
    return fabs(f1-f2)<  EPSILON;
}

void myRT::ObjectBase::SetTransformMatirx(const myRT::GTform &transformMatrix)
{
    m_transformationMatrix = transformMatrix;
}

bool myRT::ObjectBase::assignMaterial(const std::shared_ptr<myRT::MaterialBase> &objectMaterial)
{
    m_pMaterial = objectMaterial;
    m_hasMaterial = true;
    return m_hasMaterial;
}


