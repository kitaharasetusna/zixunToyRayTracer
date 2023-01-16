#ifndef MATERIALBASE_H
#define MATERIALBASE_H

#include <memory>
#include "../qbLinAlg/qbVector.h"
#include "../myPrimatives/objectBase.hpp"
#include "../myLights/lightBase.hpp"

namespace myRT
{
    class MaterialBase
    {
        public:
            MaterialBase();
            virtual ~MaterialBase();

            virtual qbVector<double> ComputeColor(const std::vector<std::shared_ptr<myRT::ObjectBase>> &objectList,
                                                  const std::vector<std::shared_ptr<myRT::LightBase>> &lightList,
                                                  const std::shared_ptr<myRT::ObjectBase> &curentObject,
                                                  const qbVector<double> &intPoint, const qbVector<double> &localNormal,
												  const myRT::Ray &cameraRay);

            //we set this static because this has nothing to do with the material itself
            static qbVector<double> ComputeDiffuseColor(const std::vector<std::shared_ptr<myRT::ObjectBase>> &objectList,
                                                  const std::vector<std::shared_ptr<myRT::LightBase>> &lightList,
                                                  const std::shared_ptr<myRT::ObjectBase> &curentObject,
                                                  const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                                  const qbVector<double> &baseColor);
        private:
        //TODO:
    };
} 



#endif