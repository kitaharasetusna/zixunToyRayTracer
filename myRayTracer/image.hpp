#ifndef IMAGE_H
#define IMAGE_H

#include<vector>
#include<SDL2/SDL.h>
class Image
{
    public:
        //constructor
        Image();
        //destructor
        ~Image();

        //initialize: for app to use
        //set image size
        //set pRender
        void Initialize(const int xSize, const int ySize, SDL_Renderer* renderer);

        void SetPixel(const int x, const int y, const double red, const double green, const double blue);
        //---------------tool functions

        //for app to use
        void Display();

        int GetXSize();

        int GetYSize();
    private:
        Uint32 ConvertColor(const double red, const double green, const double blue);
        //---------------tool functions
        //SDL pipelines
        void InitTexture();
        void ComputeMaxValues();

    private:
        SDL_Renderer *m_pRenderer;
        SDL_Texture *m_pTexture;
        //imageSize
        int m_xSize;
        int m_ySize;
        //image pixel_values_containers
        std::vector<std::vector<double>> m_rChannel;
        std::vector<std::vector<double>> m_gChannel;
        std::vector<std::vector<double>> m_bChannel;

        //store the maximum value
        double m_maxRed, m_maxGreen, m_maxBlue, m_overallMax;
};

#endif
