#ifndef GTFM_H
#define GTFM_H


#include "./qbLinAlg/qbVector.h"
#include "./qbLinAlg/qbMatrix.h"
#include "ray.hpp"


namespace myRT
{
    constexpr bool FWDGTORM = true;
    constexpr bool BWDGTORM = false;


    class GTform
    {
        public:
            GTform();
            ~GTform();


            //reload the constructor;
            //tips: we used & to reduce the trouble of copying data that are too big
            GTform(const qbMatrix2<double> &fwd, const qbMatrix2<double> &bwd);

            void SetTransform(const qbVector<double> &translation,
                             const qbVector<double> &rotation,
                             const qbVector<double> &scale);
            
            qbMatrix2<double> GetFwdMatrix();
            qbMatrix2<double> GetBwdMatrix();

            //directly apply on ray
            myRT::Ray Apply(const myRT::Ray &inputRay, bool dirFlag);
            //the true function that is called , 
            //directly apply on vector
            qbVector<double> Apply(const qbVector<double> &inputVector, bool dirFlag);

            friend GTform operator* (const myRT::GTform &lhs, const myRT::GTform &rhs);

            //overload the assign operator
            GTform operator= (const GTform &rhs);

            //tool functions for debugging
            void PrintMatrix(bool dirFlag);

            void PrintVector(const qbVector<double> &inputVector);
        
        private:
            void Print(const qbMatrix2<double> &matrix);

        private:
            qbMatrix2<double> m_fwdtm {4, 4};
            qbMatrix2<double> m_bwdtm {4, 4};


    };
} // namespace name




#endif

