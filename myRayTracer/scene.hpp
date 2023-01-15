#ifndef SCENE_H
#define SCENE_H

#include<memory>
#include<vector>

#include "image.hpp"
#include "objectshpere.hpp"
#include "camera.hpp"
#include "lightPoint.hpp"
#include "objectPlane.hpp"

namespace myRT
{
    class Scene
    {
        public:
            Scene();

            bool Render(Image &image);

        private:
        //some functions to write
            myRT::Camera m_camera;

            //a test primitive
            //myRT::ObjectShpere m_testSphere;

            //list of objects
            std::vector<std::shared_ptr<myRT::ObjectBase>> m_objectList;


            //list of lights
            std::vector<std::shared_ptr<myRT::LightBase>> m_lightList;
    };
}

#endif