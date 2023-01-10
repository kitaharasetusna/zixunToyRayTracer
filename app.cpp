#include "app.hpp"
#include "./myRayTracer/qbLinAlg/qbVector.h"

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
        
		
		// Set the background color to white.
		SDL_SetRenderDrawColor(pRender, 255, 255, 255, 255);
		SDL_RenderClear(pRender);
		
		// Render the scene.
		m_scene.Render(m_image);
		
		// Display the image.
		m_image.Display();
		
		// Show the result.
		SDL_RenderPresent(pRender);

        // // Test the camera class.
		// myRT::Camera testCamera;
		// testCamera.SetCameraPosition(qbVector<double>(std::vector<double>{0.0, 0.0, 0.0}));
		// testCamera.SetLookAtPosition(qbVector<double>(std::vector<double>{0.0, 2.0, 0.0}));
		// testCamera.SetUp(qbVector<double>(std::vector<double>{0.0, 0.0, 1.0}));
		// testCamera.SetLength(1.0);
		// testCamera.SetHorzSize(1.0);
		// testCamera.SetAspect(1.0);
		// testCamera.UpdateCameraGeometry();
		
		// // Get the screen centre and U,V vectors and display.
		// auto screenCentre = testCamera.GetScreenCentre();
		// auto screenU = testCamera.GetU();
		// auto screenV = testCamera.GetV();
		
		// // And display to the terminal.
		// std::cout << "Camera screen centre:" << std::endl;
		// PrintVector(screenCentre);
		// std::cout << "\nCamera U vector:" << std::endl;
		// PrintVector(screenU);
		// std::cout << "\nCamera V vector:" << std::endl;
		// PrintVector(screenV);



		
		// // Create some colour variations.
		// for (int x=0; x<1920; ++x)
		// {
		// 	for (int y=0; y<1200; ++y)
		// 	{
		// 		double red = (static_cast<double>(x)/1920.0) * 255.0;
		// 		double green = (static_cast<double>(y)/1200.0) * 255.0;
		// 		m_image.SetPixel(x, y, red, green, 0.0);
		// 	}
		// }


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

    m_scene.Render(m_image);
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

void CAPP::PrintVector(const qbVector<double> &inputVector)
{
	int nRows = inputVector.GetNumDims();
	for (int row = 0; row<nRows; ++row)
    {
        std::cout << std::fixed << std::setprecision(3) << inputVector.GetElement(row) << std::endl;
	} 	
}
