#include "objectPlane.hpp"

myRT::ObjectPlane::ObjectPlane()
{

}

myRT::ObjectPlane::~ObjectPlane()
{

}

bool myRT::ObjectPlane::TestIntersections(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor)
{
    //cast rat into local cooord
    myRT:Ray bwdRay = m_transformationMatrix.Apply(castRay, myRT::BWDGTORM);
    qbVector<double> k = bwdRay.m_Ray;
    k.Normalize();
    // z.y = 0 : =parallel to the plane
    if (!CloseEnough(k.GetElement(2), 0.0))
    {
        //t = a_z/-k_z
        double t = bwdRay.m_PointStart.GetElement(2) / -k.GetElement(2);
        //t<0 behind the camera
        if (t > 0.0)
		{
            //u=a_x+k_x*t
            double u = bwdRay.m_PointStart.GetElement(0) + (k.GetElement(0) * t);
            //v= a_y+k_y*t
			double v = bwdRay.m_PointStart.GetElement(1) + (k.GetElement(1) * t);
            /* If the magnitude of both u and v is less than or equal to one
				then we must be in the plane. */
            if ((abs(u) < 1.0) && (abs(v) < 1.0))
			{
                // poi = p+t*k (local coord)
                qbVector<double> poi = bwdRay.m_PointStart + t * k;
                // poi (world coord)
                intPoint = m_transformationMatrix.Apply(poi, myRT::FWDGTORM);

                qbVector<double> localOrigin {std::vector<double> {0.0, 0.0, 0.0}};
                qbVector<double> normalVector {std::vector<double> {0.0, 0.0, -1.0}};
                qbVector<double> globalOrigin = m_transformationMatrix.Apply(localOrigin, myRT::FWDGTORM);
                localNormal =m_transformationMatrix.Apply(normalVector, myRT::FWDGTORM) - globalOrigin;
                localNormal.Normalize();
				
				// Return the base color.
				localColor = m_baseColor;
                return true;
            }
            else
            {
                return false;
            }
           
        }
        else
        {
            //parallel to the palne(or close to this status )
            return false;
        }
    }
    return false;
}