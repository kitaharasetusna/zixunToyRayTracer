#ifndef CAMERA_H
#define CAMERA_H
#include "./qbLinAlg/qbVector.h"
#include "ray.hpp"

namespace myRT
{
    class Camera{
        public:
            //some public functions
            Camera();
            void SetCameraPosition	(const qbVector<double> &newPosition);
            void SetLookAtPosition		(const qbVector<double> &newLookAt);
            void SetUp				(const qbVector<double> &upVector);

            //align can be computed by LooAt-CameraPo. Norm

            //center can be computed: center = CameraPos + align*Length 
            //U can be computed: U=align X LookUp .Norm
            //V can be computed: V=U X align. Norm


            void SetLength		(double newLength);
		    void SetHorzSize	(double newSize);
		    void SetAspect		(double newAspectRatio);
            qbVector<double> 	GetPosition();
            qbVector<double> 	GetLookAt();
            qbVector<double>	GetUp();
            qbVector<double>	GetU();
            qbVector<double>	GetV();
            qbVector<double>	GetScreenCentre();
            double 						GetLength();
            double 						GetHorzSize();
            double						GetAspect();

            //update everything mentioned above
            void UpdateCameraGeometry();
            Ray GenerateRay(float proScreenX, float proScreenY);
	
		    
	

        private:
            //some private variables
            //cameraPos, Up;  align       LookAt, U, V, Center, ratio, -aspect?(no need) 
            // horizontal
            //camera_length, 
            qbVector<double> m_cameraPosition           {3};
            qbVector<double> m_cameraLookAt	            {3};
            qbVector<double> m_cameraUp		            {3};

            qbVector<double> m_alignmentVector          {3};

            qbVector<double> m_projectionScreenCentre	{3};
            qbVector<double> m_projectionScreenU		{3};
		    qbVector<double> m_projectionScreenV		{3};

            double m_cameraLength;
		    double m_cameraHorzSize;
		    double m_cameraAspectRatio;
    };
}
#endif