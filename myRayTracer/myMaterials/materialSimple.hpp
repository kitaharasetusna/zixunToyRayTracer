#ifndef MATERIALSIMPLE_H
#define MATERIALSIMPLE_H

#include "materialBase.hpp"

namespace myRT
{
    class MaterialSimple: public MaterialBase
    {
        public:
            MaterialSimple();
            virtual ~MaterialSimple();
            virtual qbVector<double> ComputeColor(const std::vector<std::shared_ptr<myRT::ObjectBase>> &objectList,
                                                    const std::vector<std::shared_ptr<myRT::LightBase>> &lightList,
                                                    const std::shared_ptr<myRT::ObjectBase> &curentObject,
                                                    const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                                    const myRT::Ray &cameraRay) override;

                //we set this static because this has nothing to do with the material itself
            qbVector<double> ComputeSpecular(const std::vector<std::shared_ptr<myRT::ObjectBase>> &objectList,
                                                    const std::vector<std::shared_ptr<myRT::LightBase>> &lightList,
                                                    const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                                    const myRT::Ray &cameraRay);
        public:
			qbVector<double> m_baseColor {std::vector<double> {1.0, 0.0, 1.0}};
			double m_reflectivity = 0.0;
			double m_shininess = 0.0;
                                            
    };
}

#endif
