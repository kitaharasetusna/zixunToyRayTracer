#include "app.hpp"

CAPP::CAPP()
{
    isRunning = true;
    pWindow = NULL;
    pRender = NULL;
}

int CAPP::OnExcute()
{
    SDL_Event event;
    if(OnInit()==0)
    {
        return -1;
    }
    
    //game loop
    while(isRunning)
    {
        while(SDL_PollEvent(&event)!=0)
        {
            OnEvent(&event); //why &event, what is the type of SDL_Event
        }
        OnRendering();
    }
    OnExit();
    return 0;
}

//tool functions
bool CAPP::OnInit()
{
    pWindow = SDL_CreateWindow("myRayTracing Toy", 
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,1920, 1200, SDL_WINDOW_SHOWN);
    if(pWindow==0)
    {
        return false;  
    }
    else
    {
        pRender = SDL_CreateRenderer(pWindow, -1, 0);//TODO: why not testing this one?

        //this is where we change color of all pixels  
        // Initialise the Image instance.
		m_image.Initialize(1920, 1200, pRender);
		
		// Create some colour variations.
		for (int x=0; x<1920; ++x)
		{
			for (int y=0; y<1200; ++y)
			{
				double red = (static_cast<double>(x)/1920.0) * 255.0;
				double green = (static_cast<double>(y)/1200.0) * 255.0;
				m_image.SetPixel(x, y, red, green, 0.0);
			}
		}
    }
    return true;
}

void CAPP::OnEvent(SDL_Event *event)
{
    if(event->type==SDL_QUIT)
    {
        isRunning=false;
    }
}

void CAPP::OnRendering()
{
    SDL_SetRenderDrawColor(pRender, 255, 255, 255, 255);
    SDL_RenderClear(pRender);
    m_image.Display();
    SDL_RenderPresent(pRender);
}

void CAPP::OnExit()
{
    SDL_DestroyRenderer(pRender);
    SDL_DestroyWindow(pWindow);
    pRender = NULL;
    pWindow = NULL;
    SDL_Quit();
}