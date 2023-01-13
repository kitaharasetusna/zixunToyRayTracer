#include "gtform.hpp"

myRT::GTform::GTform()
{
    m_fwdtm.SetToIdentity();
    m_bwdtm.SetToIdentity();
}

myRT::GTform::~GTform()
{

}

myRT::GTform::GTform(const qbMatrix2<double> &fwd, const qbMatrix2<double> &bwd)
{
    //check if the shape is right
    if(fwd.GetNumRows()!=4 ||fwd.GetNumCols()!=4 ||
        bwd.GetNumRows()!=4 ||bwd.GetNumCols()!=4)
    {
        throw std::invalid_argument("Cannot construct GTform, inputs are not all 4x4.\nCheck the dim of fwd or bwd");
    }
    m_fwdtm = fwd;
    m_bwdtm = bwd;
}

void myRT::GTform::SetTransform(const qbVector<double> &translation,
                             const qbVector<double> &rotation,
                             const qbVector<double> &scale)
{
    //A = T*S*R_x*R_y*R_z
    qbMatrix2<double> translationMatrix	{4, 4};
    qbMatrix2<double>	scaleMatrix	{4, 4};
	qbMatrix2<double> rotationMatrixX	{4, 4};
	qbMatrix2<double>	rotationMatrixY	{4, 4};
	qbMatrix2<double> rotationMatrixZ	{4, 4};

    translationMatrix.SetToIdentity();
	rotationMatrixX.SetToIdentity();
	rotationMatrixY.SetToIdentity();
	rotationMatrixZ.SetToIdentity();
	scaleMatrix.SetToIdentity();

    // Populate these with the appropriate values.
	// First the translation matrix.
	translationMatrix.SetElement(0, 3, translation.GetElement(0));
	translationMatrix.SetElement(1, 3, translation.GetElement(1));
	translationMatrix.SetElement(2, 3, translation.GetElement(2));
	
	// Rotation matrices.
	rotationMatrixZ.SetElement(0, 0, cos(rotation.GetElement(2)));
	rotationMatrixZ.SetElement(0, 1, -sin(rotation.GetElement(2)));
	rotationMatrixZ.SetElement(1, 0, sin(rotation.GetElement(2)));
	rotationMatrixZ.SetElement(1, 1, cos(rotation.GetElement(2)));
	
	rotationMatrixY.SetElement(0, 0, cos(rotation.GetElement(1)));
	rotationMatrixY.SetElement(0, 2, sin(rotation.GetElement(1)));
	rotationMatrixY.SetElement(2, 0, -sin(rotation.GetElement(1)));
	rotationMatrixY.SetElement(2, 2, cos(rotation.GetElement(1)));
	
	rotationMatrixX.SetElement(1, 1, cos(rotation.GetElement(0)));
	rotationMatrixX.SetElement(1, 2, -sin(rotation.GetElement(0)));
	rotationMatrixX.SetElement(2, 1, sin(rotation.GetElement(0)));
	rotationMatrixX.SetElement(2, 2, cos(rotation.GetElement(0)));
	
	// And the scale matrix.
	scaleMatrix.SetElement(0, 0, scale.GetElement(0));
	scaleMatrix.SetElement(1, 1, scale.GetElement(1));
	scaleMatrix.SetElement(2, 2, scale.GetElement(2));

    // Combine to give the final forward transform matrix.
	m_fwdtm =	translationMatrix * 
			scaleMatrix *
			rotationMatrixX *
			rotationMatrixY *
			rotationMatrixZ;
							
	// Compute the backwards transform.
	m_bwdtm = m_fwdtm;
	m_bwdtm.Inverse();
	
}

qbMatrix2<double> myRT::GTform::GetFwdMatrix()
{
    return m_fwdtm;
}

qbMatrix2<double> myRT::GTform::GetBwdMatrix()
{
    return m_bwdtm;
}

myRT::Ray myRT::GTform::Apply(const myRT::Ray &inputRay, bool dirFlag)
{
    myRT::Ray outputRay;

    if(dirFlag)
    {
        outputRay.m_PointStart = this->Apply(inputRay.m_PointStart, myRT::FWDGTORM);
        outputRay.m_PointEnd = this->Apply(inputRay.m_PointEnd, myRT::FWDGTORM);
        outputRay.m_Ray = outputRay.m_PointEnd-outputRay.m_PointStart;
    }
    else
    {
        outputRay.m_PointStart = this->Apply(inputRay.m_PointStart, myRT::BWDGTORM);
        outputRay.m_PointEnd = this->Apply(inputRay.m_PointEnd, myRT::BWDGTORM);
        outputRay.m_Ray = outputRay.m_PointEnd-outputRay.m_PointStart;
    }
    return outputRay;
}


//the real apply function that works on rays(vectors)
qbVector<double> myRT::GTform::Apply(const qbVector<double> &inputVector, bool dirFlag)
{
    // Convert inputVector to a 4-element vector.
	std::vector<double> tempData {	inputVector.GetElement(0),
					inputVector.GetElement(1),
					inputVector.GetElement(2),
					1.0 };
	qbVector<double> tempVector {tempData};
    //done 

    // Create a vector for the result.
	qbVector<double> resultVector;
	
	if (dirFlag)
	{
		// Apply the forward transform.
		resultVector = m_fwdtm * tempVector;
	}
	else
	{
		// Apply the backward transform.
		resultVector = m_bwdtm * tempVector;
	}
	
	// Reform the output as a 3-element vector.
	qbVector<double> outputVector {std::vector<double> {	resultVector.GetElement(0),
								resultVector.GetElement(1),
								resultVector.GetElement(2) }};
																					
	return outputVector;
}

/// reload the operator
namespace myRT
{
    myRT::GTform operator* (const myRT::GTform &lhs, const myRT::GTform &rhs)
    {
        qbMatrix2<double> fwdResult = lhs.m_fwdtm * rhs.m_fwdtm;
        qbMatrix2<double> bckResult = fwdResult;
		bckResult.Inverse();
		// Form the final result.
		myRT::GTform finalResult (fwdResult, bckResult);
		return finalResult;
    }
}

// Overload the assignment operator.
myRT::GTform myRT::GTform::operator= (const myRT::GTform &rhs)
{
	// Make sure that we're not assigning to ourself.
	if (this != &rhs)
	{
		m_fwdtm = rhs.m_fwdtm;
		m_bwdtm = rhs.m_bwdtm;
	}
	return *this;
}

// Function to print the transform matrix to STDOUT.
void myRT::GTform::PrintMatrix(bool dirFlag)
{
	if (dirFlag)
	{
		Print(m_fwdtm);
	}
	else
	{
		Print(m_bwdtm);
	}
}

void myRT::GTform::PrintVector(const qbVector<double> &inputVector)
{
    int nRows = inputVector.GetNumDims();
	for (int row = 0; row < nRows; ++row)
	{
		std::cout << std::fixed << std::setprecision(3) << inputVector.GetElement(row) << std::endl;
	}
}


void myRT::GTform::Print(const qbMatrix2<double> &matrix)
{
    int nRows = matrix.GetNumRows();
	int nCols = matrix.GetNumCols();
	for (int row = 0; row<nRows; ++row)
	{
		for (int col = 0; col<nCols; ++col)
		{
			std::cout << std::fixed << std::setprecision(3) << matrix.GetElement(row, col) << " ";
		}
		std::cout << std::endl;
	}
}


