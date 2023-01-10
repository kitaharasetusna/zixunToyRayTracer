#include "objectshpere.hpp"

myRT::ObjectShpere::ObjectShpere()
{

}

myRT::ObjectShpere::~ObjectShpere()
{

}

//Very Important!!!!!!
bool myRT::ObjectShpere::TestIntersections(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double>)
{
    //input: castRay
    //output: intersect or not and a bunch of 

    //get unit dir of castRay
    qbVector<double> vhat = castRay.m_Ray;
    vhat.Normalize();

    //refer formular
    //a = dot(vhat, vhat)=module(vhat)=1;
    //b = 2*dot(castRay.m_Start, vhat);
    //c = dot(castRay.m_Start, castRay.m_Start)-r**2
    //t = {-b+/-sqrt(b^2-4a*c)}/2a
    //b^2-4*a*c>0
    //double a = 1;

    double b = 2.0*qbVector<double>::dot(castRay.m_PointStart, vhat);

    double c = qbVector<double>::dot(castRay.m_PointStart, castRay.m_PointStart) -1.0;

    double intTest = (b*b) - 4.0*c;

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
				intPoint = castRay.m_PointStart + (vhat * t1);
			}
			else
			{
				intPoint = castRay.m_PointStart + (vhat * t2);
			}
        }
        return true;
    }
    else
    {
        return false;
    }
}