#include "objectShpere.hpp"

myRT::ObjectShpere::ObjectShpere()
{

}

myRT::ObjectShpere::~ObjectShpere()
{

}

//Very Important!!!!!!
//return intersection point (world coord)
//and localNormal(world coord)
bool myRT::ObjectShpere::TestIntersections(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor)
{
    myRT::Ray bkwRay = m_transformationMatrix.Apply(castRay, myRT::BWDGTORM);
    //input: castRay
    //output: intersect or not and a bunch of 

    //get unit dir of castRay
    qbVector<double> vhat = bkwRay.m_Ray;
    vhat.Normalize();

    //refer formular
    //a = dot(vhat, vhat)=module(vhat)=1;
    //b = 2*dot(castRay.m_Start, vhat);
    //c = dot(castRay.m_Start, castRay.m_Start)-r**2
    //t = {-b+/-sqrt(b^2-4a*c)}/2a
    //b^2-4*a*c>0
    //double a = 1;

    double b = 2.0*qbVector<double>::dot(bkwRay.m_PointStart, vhat);

    double c = qbVector<double>::dot(bkwRay.m_PointStart, bkwRay.m_PointStart) -1.0;

    double intTest = (b*b) - 4.0*c;

    
    qbVector<double> poi;
    if(intTest>0.0)
    {
        double numSQRT = sqrtf(intTest);
		double t1 = (-b + numSQRT) / 2.0;
		double t2 = (-b - numSQRT) / 2.0;
        //outside the camera
        if ((t1 < 0.0) || (t2 < 0.0))
		{
			return false;
		}
        else
        {
            // Determine which point of intersection was closest to the camera.
            //  X=P+t*vhat 
			if (t1 < t2)
			{
                //point of intersection
				poi = bkwRay.m_PointStart + (vhat * t1);
			}
			else
			{
				poi = bkwRay.m_PointStart + (vhat * t2);
			}



            //transform back to the original world
            // Transform the intersection point back into world coordinates.
			intPoint = m_transformationMatrix.Apply(poi, myRT::FWDGTORM);
			
			// objOrigin is the orgin point of local coord and we transform it into the world coord
			qbVector<double> objOrigin = qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}};
			qbVector<double> newObjOrigin = m_transformationMatrix.Apply(objOrigin, myRT::FWDGTORM);
            localNormal = intPoint-newObjOrigin;
			localNormal.Normalize();

            localColor = m_baseColor;
        }
        
        return true;
    }
    else
    {
        return false;
    }
}