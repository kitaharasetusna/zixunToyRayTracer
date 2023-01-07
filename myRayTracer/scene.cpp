#include "scene.hpp"

myRT::Scene::Scene()
{

}


bool myRT::Scene::Render(Image &image)
{
    int m_xSize = image.GetXSize();
    int m_ySize = image.GetYSize();
    //get gradient color
    for(int i=0; i<m_xSize; i++)
        for(int j=0; j<m_ySize; j++)
            {
                double red = (static_cast<double>(i))/(static_cast<double>(m_xSize))*255;
                double green  = (static_cast<double>(j)/(static_cast<double>(m_ySize)))*255;
                image.SetPixel(i, j, red, green, 0.0);
            }
    return true;
}