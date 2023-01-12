#include "lightBase.hpp"

myRT::LightBase::LightBase()
{

}

myRT::LightBase::~LightBase()
{

}

bool myRT::LightBase::computeIllumination(const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                        const std::vector<std::shared_ptr<myRT::ObjectBase>> &objectList,
                                        const std::shared_ptr<myRT::ObjectBase> & currentObject,
                                        qbVector<double>&color, double &intensity)
{
    return false;
}