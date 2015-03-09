#include "matrix.h"

/*
 * Matrix class
 */

Matrix4::Matrix4()
{
	for (int i = 0; i < m_NUMBER_ELEMENTS; ++i)
	{
		mElements[i] = 0;
	}
}

// Constructs a matrix given an array of values.
Matrix4::Matrix4(double* elements)
{
	for (int i = 0; i < m_NUMBER_ELEMENTS; ++i)
	{
		mElements[i] = elements[i];
	}
}

// Constructs a matrix given individual values.
Matrix4::Matrix4(double a11, double a12, double a13, double a14,
				double a21, double a22, double a23, double a24,
				double a31, double a32, double a33, double a34,
				double a41, double a42, double a43, double a44)
{
	mElements[0] = a11;		mElements[1] = a12;		mElements[2] = a13;		mElements[3] = a14;
	mElements[4] = a21;		mElements[5] = a22;		mElements[6] = a23;		mElements[7] = a24;
	mElements[8] = a31;		mElements[9] = a32;		mElements[10] = a33;	mElements[11] = a34;
	mElements[12] = a41;	mElements[13] = a42;	mElements[14] = a43;	mElements[15] = a44;
}

// Returns the matrix element mapped to by the 0-based subscripts "i" and "j".
const double Matrix4::operator()(unsigned short i, unsigned short j)
{
	return mElements[4 * i + j];
}

// Set the matrix element mapped to by the 0-based subscripts "i" and "j" to the input "value".
void Matrix4::operator()(unsigned short i, unsigned short j, double value)
{
	mElements[4 * i + j] = value;
}

void Matrix4::toFloatArray(float* floatArray)
{
	for (int i = 0; i < m_NUMBER_ELEMENTS; ++i)
	{
		floatArray[i] = (float)mElements[i];
	}
}

const Matrix4 Matrix4::inverse(void)
{
	// If determinant is zero, the matrix is not invertible. In that case, the original matrix is returned.
	if (determinant() == 0)
	{
		return *this;
	}

	// TODO: Finish this method.
}

Matrix4 Matrix4::identity(void)
{
	return Matrix4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
}

const float Matrix4::determinant(void)
{
	return ((*this)(1, 1) * (*this)(2, 2) * (*this)(3, 3));
}
