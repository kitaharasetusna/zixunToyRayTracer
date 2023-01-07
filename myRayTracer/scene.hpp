#ifndef SCENE_H
#define SCENE_H

#include "image.hpp"

namespace myRT
{
    class Scene
    {
        public:
            Scene();

            bool Render(Image &image);

        private:
        //some functions to write
    };
}

#endif