#ifndef LIGHTBASE_H
#define LIGHTBASE_H

#include <memory>
#include "./qbLinAlg/qbVector.h"
#include "ray.hpp"
#include "objectBase.hpp"

namespace myRT
{
    class LightBase
    {
        public:
        LightBase();
        virtual ~LightBase();

        virtual bool computeIllumination(const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                        const std::vector<std::shared_ptr<myRT::ObjectBase>> &objectList,
                                        const std::shared_ptr<myRT::ObjectBase> & currentObject,
                                        qbVector<double>&color, double &intensity);

        public:
            //color light location of the light
			qbVector<double>	m_color		{3};
			qbVector<double>	m_location	{3};
			double				m_intensity;
    };
}



#endif