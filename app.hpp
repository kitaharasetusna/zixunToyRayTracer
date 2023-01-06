#ifndef C_APP_H
#define C_APP_H

#include "./myRayTracer/image.hpp"
#include<SDL2/SDL.h>

//A class dealing with windows and input from user
class CAPP
{
    public:
        CAPP();
        int OnExcute();
        bool OnInit();
        void OnEvent(SDL_Event *event);
        void OnRendering();
        void OnExit();

    private:
        //some SDL2 stuff
        bool isRunning;
        SDL_Window  *pWindow;
        SDL_Renderer *pRender; 

        Image m_image;

};

#endif