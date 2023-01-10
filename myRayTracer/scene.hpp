#ifndef SCENE_H
#define SCENE_H

#include "image.hpp"
#include "objectshpere.hpp"
#include "camera.hpp"

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
            myRT::ObjectShpere m_testSphere;
    };
}

#endif