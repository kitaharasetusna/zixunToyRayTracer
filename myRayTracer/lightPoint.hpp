#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "lightBase.hpp"

namespace myRT
{
    class LightPoint: public LightBase
    {
        public:
            LightPoint();

            virtual ~LightPoint() override;

            virtual bool computeIllumination(const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                            const std::vector<std::shared_ptr<myRT::ObjectBase>> &objectList,
                                            const std::shared_ptr<myRT::ObjectBase> & currentObject,
                                            qbVector<double>&color, double &intensity) override;
    };

}

#endif